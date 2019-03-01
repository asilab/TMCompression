#!/bin/bash
#
# ==============================================================================
#Verify if there are inputs
# ==============================================================================

if [ $# -eq 0 ]; then
    echo "No arguments provided"
    exit 1
fi

# ==============================================================================
# Options
# ==============================================================================
INSTALL_GOOSE=$1;
CARDINALITY=$2;
STATE2_TMs=$3;
STATE3_TMs=$4;
Profile=1;
# ==============================================================================
# Install Goose
# ==============================================================================

if [[ "$INSTALL_GOOSE" -eq "1" ]];
    then
    rm -r goose
    git clone https://github.com/pratas/goose.git
    cd goose/src/
    make
    cd ../../
fi

# ==============================================================================
# Process Results of cardinality
# ==============================================================================
if [[ "$CARDINALITY" -eq "1" ]];
    then
    ./tm --tmgrowth > Cardinality.txt
    tail -n +2 Cardinality.txt | head -n -20 > Cardinality2.txt

    gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "Cardinality.pdf"
    set style line 1 lt rgb "red" lw 3
    set xrange [0:100]
    set yrange [0:]
    set grid ytics lt -1
    set style fill solid
    set xlabel "Number of States"
    set ylabel "Number of Turing Machines"
    set format y "10^{%L}"
    set logscale y 10
    f(x) = (2*x*3)**(x*2)
    set datafile separator "\t"
    set xtics
    set style fill transparent solid 0.5 noborder
    plot f(x)  ls 1 title "f(x) = (6x)^2^x", 'Cardinality2.txt' using 1:2 linecolor '#4169E1' pointtype 7  pointsize 0.5 lw 0.5 title "Growth in Number of TMs"
EOF
rm Cardinality.txt Cardinality2.txt
mv Cardinality.pdf ./results
fi


# ==============================================================================
# Process Results of 2 state Turing Machines
# ==============================================================================

if [[ "$STATE2_TMs" -eq "1" ]];
    then
    var="2st.txt";
    tail -n +4 $var | head -n -3 | ./ioNormalize $var >  2stResults.txt
    #Amplitude
    awk '{ print $4;}' 2stResults.txt | ./goose/bin/goose-filter -w 201 -d 5 -1 > Amplitude.txt; 
    #nmvc
    awk '{ print $5;}' 2stResults.txt | ./goose/bin/goose-filter -w 201 -d 5 -1 > nmvc.txt;
    #nc
    awk '{ print $6;}' 2stResults.txt | ./goose/bin/goose-filter -w 201 -d 5 -1 > NC_f.txt;

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "2sts.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:20736]
    set yrange [:]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "2 state Turing Machines 0 to 20736"
    set datafile separator "\t"
    ntics = 100
    stats 'Amplitude.txt' using 1 name 'x' nooutput
    set xtics int(x_max/ntics)*5
    set style fill transparent solid 0.6 noborder
    plot "Amplitude.txt" using 1:2 with boxes linecolor '#CFB53B' title "Amplitude of Tape", "NC_f.txt" using 1:2  with boxes linecolor '#4169E1' title "Normalized Compression", "nmvc.txt" using 1:2 with boxes linecolor '#3D9970' title "NMVC"
EOF
    mv 2sts.pdf ./results
    rm Amplitude.txt nmvc.txt NC_f.txt 2stResults.txt
fi


# ==============================================================================
# Process Results of 3 state Turing Machines
# ==============================================================================

if [[ "$STATE3_TMs" -eq "1" ]];
    then


    var="3st";
    text=$var".txt"
    tail -n +4 $text | head -n -3 | ./ioNormalize $text >  $var"Results.txt"
    #Amplitude
    awk '{ print $4;}' $var"Results.txt" | ./goose/bin/goose-filter -w 1001 -d 1000 -1 > Amplitude3.txt; 
    #nmvc
    awk '{ print $5;}' $var"Results.txt" | ./goose/bin/goose-filter -w 1001 -d 1000 -1 > nmvc3.txt;
    #nc
    awk '{ print $6;}' $var"Results.txt" | ./goose/bin/goose-filter -w 1001 -d 1000 -1 > NC_f3.txt;
    
gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "3sts.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:34012224]
    set yrange [0:]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "3 state Turing Machines 0 to 34012224"
    set datafile separator "\t"
    ntics = 10
    stats 'nmvc3.txt' using 1 name 'x' nooutput
    set xtics int(x_max/ntics)
    set style fill transparent solid 0.4 noborder
    plot "Amplitude3.txt" using 1:2 with boxes linecolor '#CFB53B' title "Amplitude of Tape", "NC_f3.txt" using 1:2  with boxes linecolor '#4169E1' title "Normalized Compression"
EOF
    #, "nmvc3.txt" using 1:2 with boxes linecolor '#3D9970' title "NMVC"
    mv 3sts.pdf ./results
    rm  Amplitude3.txt nmvc3.txt NC_f3.txt 3stResults.txt
fi

