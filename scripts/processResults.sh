#!/bin/bash
#
# ==============================================================================
#Verify if there are inputs
# ==============================================================================
if [ $# -ne 5 ]; then
    echo "Not enough arguments arguments provided, you need to provide 5 arguments:";
    echo "All args are boolean (0 or 1)";
    echo "";
    echo "If 1st Argument == 1: Installs goose in your system, which is required for result processing";
    echo "bash processResults.sh 1 0 0 0 0";
    echo "";
    echo "If 2nd Argument == 1:Creates plot of TM Cardinality Growth";
    echo "bash processResults.sh 0 1 0 0 0";
    echo "";
    echo "If 3rd Argument == 1:Creates plot of all TM with #Alphabet=2, #States=2";
    echo "bash processResults.sh 0 0 1 0 0";
    echo "";
    echo "If 4th Argument == 1:Creates plot of all TM with #Alphabet=2, #States=3";
    echo "bash processResults.sh 0 0 0 1 0";
    echo "";
    echo "If 5th Argument == 1:Creates plot of all TM with #Alphabet=3, #States=2";
    echo "bash processResults.sh 0 0 0 0 1";
    echo "";
    exit 1;
fi

# ==============================================================================
# Options
# ==============================================================================
INSTALL_GOOSE=$1;
CARDINALITY=$2;
STATE2_TMs=$3;
STATE3_TMs=$4;
STATE2_ALPH3_TMs=$5;
# ==============================================================================
# Install Goose
# ==============================================================================

if [[ "$INSTALL_GOOSE" -eq "1" ]];
    then
    cd ..;
    echo "Installing goose in your system, which is required for result processing ...";
    
    rm -r goose;
    git clone https://github.com/pratas/goose.git;
    cd goose/src/;
    make;
    cd ../../;
fi

# ==============================================================================
# Process Results of cardinality
# ==============================================================================

if [[ "$CARDINALITY" -eq "1" ]];
    then
    cd ..;
    echo "Creating plot of Turing Machine Cardinality Growth with the increase in number of states.. ";
    ./tm --tmgrowth > Cardinality.txt;
    tail -n +2 Cardinality.txt | head -n -20 > Cardinality2.txt;
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
    rm Cardinality.txt Cardinality2.txt;
    mv Cardinality.pdf ./resultPlots;
    cd ./scripts;
fi

# ==============================================================================
# Process Results of 2 state Turing Machines
# ==============================================================================

if [[ "$STATE2_TMs" -eq "1" ]];
    then
    echo "Creating plot of of all TM with #Alphabet=2, #States=2... ";
    cd ../resultText;
    pwd;
    var="2sts2alp";
    text=$var".txt";
    results=${var}Results.txt;
    echo $var"Results.txt";
    tail -n +4 $text | head -n -3 | ../ioStNormalize $text > $results;
    
    #Amplitude
    awk '{ print $4;}' $results | ../goose/bin/goose-filter -w 80 -d 5 -1 > Amplitude.txt; 
    
    #nc
    awk '{ print $6;}' $results | ../goose/bin/goose-filter -w 80 -d 5 -1 > NC_f.txt;
  
gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "2sts2alp.pdf"
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
    plot "Amplitude.txt" using 1:2 with boxes linecolor '#CFB53B' title "Amplitude of Tape", "NC_f.txt" using 1:2  with boxes linecolor '#4169E1' title "Normalized Compression"
EOF
    mv 2sts2alp.pdf ../resultPlots;
    rm Amplitude.txt NC_f.txt $results;
    cd ../scripts;
fi

# ==============================================================================
# Process Results of 3 state Turing Machines
# ==============================================================================

if [[ "$STATE3_TMs" -eq "1" ]];
    then
    echo " Creating plot of of all TM with #Alphabet=2, #States=3 ... ";
    cd ../resultText;
    pwd;
    echo"jorge Silva --------------"
    var="3sts2alp";
    text=${var}.txt;
    results=${var}Results.txt;
    tail -n +4 $text | head -n -3 | ../ioStNormalize $text > $results;
    #Amplitude
    awk '{ print $4;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 > Amplitude3.txt; 
    #nc
    awk '{ print $6;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 > NC_f3.txt;
    
gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "3sts2alp.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:34012224]
    set yrange [0:1]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "3 state Turing Machines 0 to 34012224"
    set datafile separator "\t"
    ntics = 20
    stats 'Amplitude3.txt' using 1 name 'x' nooutput
    set xtics int(x_max/ntics)
    set style fill transparent solid 0.4 noborder
    plot "Amplitude3.txt" using 1:2 with boxes linecolor '#CFB53B' title "Amplitude of Tape", "NC_f3.txt" using 1:2  with boxes linecolor '#4169E1' title "Normalized Compression"
EOF
    mv 3sts2alp.pdf ../resultPlots;
    rm Amplitude3.txt NC_f3.txt; 
    rm  $results;
    cd ../scripts;
fi

# ==============================================================================
# Process Results of 2 state Turing Machines and 3 alphabet letters
# ==============================================================================

if [[ "$STATE2_ALPH3_TMs" -eq "1" ]];
    then
    cd ../resultText;
    echo "Creating plot of of all TM with #Alphabet=3, #States=2... ";
    var="2sts3alp";
    text=${var}.txt;
    results=${var}Results.txt;
    
    tail -n +4 $text | head -n -3 | ../ioStNormalize $text > $results;
    
    #Amplitude
    awk '{ print $4;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 > AmplitudeSt2Alp3.txt; 
    #nc
    awk '{ print $6;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 > NC_f3St2Alp3.txt;
    
gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "2sts3alp.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:34012224]
    set yrange [0:1]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "2 State, 3 Alphabet Turing Machines 0 to 34012224"
    set datafile separator "\t"
    ntics = 20
    stats 'AmplitudeSt2Alp3.txt' using 1 name 'x' nooutput
    set xtics int(x_max/ntics)
    set style fill transparent solid 0.4 noborder
    plot "AmplitudeSt2Alp3.txt" using 1:2 with boxes linecolor '#CFB53B' title "Amplitude of Tape", "NC_f3St2Alp3.txt" using 1:2  with boxes linecolor '#4169E1' title "Normalized Compression"
EOF
    mv  2sts3alp.pdf ../resultPlots;
    rm  AmplitudeSt2Alp3.txt NC_f3St2Alp3.txt;
    rm  $results;
    cd ../scripts;
fi