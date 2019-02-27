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
    tail -n +4 2st.txt | head -n -3 | awk '{ print $4;}'> Amplitude 
    
    maxnum=$(sort -n Amplitude |tail -1);
    cat Amplitude | while read i; 
    do echo "scale = 10; $i/($maxnum) " | bc; 
    done > NormAmplitude
    cat NormAmplitude | ./goose/bin/goose-filter -w 201 -d 5 -1 > Amplitude.txt; 

    tail -n +4 2st.txt | head -n -3 | awk '{ print $5;}' > selfC; 
    maxnum=$(sort -n selfC |tail -1);
    cat selfC | while read i; 
    do echo "scale = 10; $i/($maxnum * 0.5) " | bc; 
    done > NormselfC
    cat NormselfC | ./goose/bin/goose-filter -w 201 -d 5 -1 > NormselfC.txt;
    
    tail -n +4 2st.txt | head -n -3 | awk '{ print $6;}'| ./goose/bin/goose-filter -w 201 -d 5 -1 > NC_f.txt;
    
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
    set style fill transparent solid 0.4 noborder
    plot "Amplitude.txt" using 1:2 with boxes linecolor '#CFB53B' title "Amplitude of Tape", "NormselfC.txt" using 1:2 with boxes linecolor '#3D9970' title "NMVC", "NC_f.txt" using 1:2  with boxes linecolor '#4169E1' title "Normalized Compression"
EOF
    mv 2sts.pdf ./results
    rm  NormselfC selfC Amplitude NormAmplitude 
fi


# ==============================================================================
# Process Results of 3 state Turing Machines
# ==============================================================================

if [[ "$STATE3_TMs" -eq "1" ]];
    then
    tail -n +4 3st.txt | head -n -3 | awk '{ print $4;}'> Amplitude3 
    
    maxnum=$(sort -n Amplitude3 | tail -1);
    cat Amplitude3 | while read i; 
    do echo "scale = 10; $i/($maxnum) " | bc; 
    done > NormAmplitude3
    cat NormAmplitude3 | ./goose/bin/goose-filter -w 201 -d 20 -1  > Amplitude3.txt; 
    

    tail -n +4 3st.txt | head -n -3 | awk '{ print $5;}' > selfC3; 
    maxnum=$(sort -n selfC3 |tail -1);
    cat selfC3 | while read i; 
    do echo "scale = 10; $i/($maxnum * 0.5) " | bc; 
    done > NormselfC3
    cat NormselfC3 | ./goose/bin/goose-filter -w 201 -d 20 -1  > NormselfC3.txt;
    
    tail -n +4 3st.txt | head -n -3 | awk '{ print $6;}'| ./goose/bin/goose-filter -w 201 -d 20 -1 > NC_f3.txt;
    
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
    set style fill transparent solid 0.4 noborder
    plot "Amplitude3.txt" using 1:2 with boxes linecolor '#CFB53B' title "Amplitude of Tape", "NormselfC3.txt" using 1:2 with boxes linecolor '#3D9970' title "NMVC", "NC_f3.txt" using 1:2  with boxes linecolor '#4169E1' title "Normalized Compression"
EOF
    mv 3sts.pdf ./Results
    rm  NormselfC3 selfC3 Amplitude3 NormAmplitude3 
fi