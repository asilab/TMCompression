#!/bin/bash
#
# ==============================================================================
#Verify if there are inputs
# ==============================================================================
if [ $# -ne 8 ]; then
    echo "Not enough arguments arguments provided, you need to provide 8 arguments:";
    echo "All args are boolean (0 or 1)";
    echo "";
    echo "If 1st Argument == 1: Installs goose in your system, which is required for result processing";
    echo "bash processResults.sh 1 0 0 0 0 0 0 0";
    echo "";
    echo "If 2nd Argument == 1:Creates plot of TM Cardinality Growth";
    echo "bash processResults.sh 0 1 0 0 0 0 0 0";
    echo "";
    echo "If 3rd Argument == 1:Creates plot of all TM with #Alphabet=2, #States=2";
    echo "bash processResults.sh 0 0 1 0 0 0 0 0";
    echo "";
    echo "If 4th Argument == 1:Creates plot of all TM with #Alphabet=2, #States=3";
    echo "bash processResults.sh 0 0 0 1 0 0 0 0";
    echo "";
    echo "If 5th Argument == 1:Creates plot of all TM with #Alphabet=3, #States=2";
    echo "bash processResults.sh 0 0 0 0 1 0 0 0";
    echo "";
    echo "If 6th Argument == 1:Creates plot of all TM with #Alphabet=2, #States=4 with MonteCarlo Algorithm";
    echo "bash processResults.sh 0 0 0 0 0 1 0 0";
    echo "";
    echo "If 7th Argument == 1:Creates plot of all TM with #Alphabet=2, #States=5 with MonteCarlo Algorithm";
    echo "bash processResults.sh 0 0 0 0 0 0 1 0";
    echo "";
    echo "If 8th Argument == 1:Creates plot of all TM with #Alphabet=2, #States=5 with MonteCarlo Algorithm";
    echo "bash processResults.sh 0 0 0 0 0 0 0 1";
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
STATE4_ALPH2_TMs=$6;
STATE5_ALPH2_TMs=$7;
STATE6_ALPH2_TMs=$8;
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
    ./tm --tmgrowth | head -n +80 |tail -n 79 > Cardinality.txt;
    gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "Cardinality.pdf"
    set style line 1 lt rgb "red" lw 3
    set xrange [0:50]
    set yrange [0:]
    set key left top
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
    plot f(x)  ls 1 title "f(x) = (6x)^2^x", 'Cardinality.txt' using 1:2 linecolor '#4169E1' pointtype 7  pointsize 0.5 lw 0.5
EOF
    rm Cardinality.txt;
    mv Cardinality.pdf ./resultPlots;
    cd ./scripts;
fi

# ==============================================================================
# Process Results of 2 State Turing Machines
# ==============================================================================

if [[ "$STATE2_TMs" -eq "1" ]];
    then
    echo "Creating plot of of all TM with #Alphabet=2, #States=2... ";
    cd ../resultText;

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
    set yrange [0:1]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "#State=2, #Alphabet=2 TM 0 to 20736"
    set datafile separator "\t"
    ntics = 100
    stats 'Amplitude.txt' using 1 name 'x' nooutput
    set xtics int(x_max/ntics)*5
    set style fill transparent solid 0.4 noborder
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
    echo "Creating plot of of all TM with #Alphabet=2, #States=3 ... ";
    cd ../resultText;
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
    set xlabel "#State=3, #Alphabet=2 TM 0 to 34012224"
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
    awk '{ print $6;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 > NC_fSt2Alp3.txt;
    
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
    set xlabel "#State=2, #Alphabet=3 TM 0 to 34012224"
    set datafile separator "\t"
    ntics = 20
    stats 'AmplitudeSt2Alp3.txt' using 1 name 'x' nooutput
    set xtics int(x_max/ntics)
    set style fill transparent solid 0.4 noborder
    plot "AmplitudeSt2Alp3.txt" using 1:2 with boxes linecolor '#CFB53B' title "Amplitude of Tape", "NC_fSt2Alp3.txt" using 1:2  with boxes linecolor '#4169E1' title "Normalized Compression"
EOF
    mv  2sts3alp.pdf ../resultPlots;
    rm  AmplitudeSt2Alp3.txt NC_fSt2Alp3.txt;
    rm  $results;
    cd ../scripts;
fi

# =======================================================================================
# Process Results of 4 state Turing Machines and 2 alphabet letters Monte Carlo Algorithm
# =======================================================================================
if [[ "$STATE4_ALPH2_TMs" -eq "1" ]];
    then
    cd ../resultText;
    echo "Creating plot of of all TM with #Alphabet=2, #States=4 Monte Carlo... ";
    
    var="4sts2alp";
    text=${var}.txt;
    results=${var}Results.txt;

    # tail -n +4 $text | head -n -3 | sort -k1 -n > new;
    # mv new $text
    < $text ../ioStNormalize $text > $results;
    
    #Amplitude
    awk '{ print $4;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 -p1> AmplitudeSt4Alp2l.txt; 
    
    #nc
    awk '{ print $6;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 -p1 > NC_fSt4Alp2l.txt;
    
    #tmIndex
    awk '{ print $1;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 -p1 > tmIndex.txt

    paste tmIndex.txt AmplitudeSt4Alp2l.txt > AmplitudeSt4Alp2.txt;
    paste tmIndex.txt NC_fSt4Alp2l.txt > NC_fSt4Alp2.txt;

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "4sts2alp-MonteCarlo.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75 
    set xrange [0:110075314176]
    set yrange [0:1]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "#State=4, #Alphabet=2 TM 0 to 110075314176 Monte Carlo"
    set datafile separator "\t"
    ntics = 20
    stats 'AmplitudeSt4Alp2.txt' using 1 name 'x' nooutput
    set xtics int(x_max/ntics)
    set style fill transparent solid 0.4 noborder
    plot "AmplitudeSt4Alp2.txt" using 1:2 with boxes linecolor '#CFB53B' title "Amplitude of Tape", "NC_fSt4Alp2.txt" using 1:2  with boxes linecolor '#4169E1' title "Normalized Compression"
EOF
    mv  4sts2alp-MonteCarlo.pdf ../resultPlots;
    rm  AmplitudeSt4Alp2.txt NC_fSt4Alp2.txt NC_fSt4Alp2l.txt AmplitudeSt4Alp2l.txt tmIndex.txt;
    rm  $results;
    cd ../scripts;
fi



# =======================================================================================
# Process Results of 5 state Turing Machines and 2 alphabet letters Monte Carlo Algorithm
# =======================================================================================
if [[ "$STATE5_ALPH2_TMs" -eq "1" ]];
    then
    cd ../resultText;
    echo "Creating plot of of all TM with #Alphabet=2, #States=5 Monte Carlo... ";
    
    var="5sts2alp";
    text=${var}.txt;
    results=${var}Results.txt;

    # tail -n +4 $text | head -n -3 | sort -k1 -n > new;
    # mv new $text
    
    < $text ../ioStNormalize $text > $results;
    
    #Amplitude
    awk '{ print $4;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 -p1> AmplitudeSt5Alp2l.txt; 
    
    #nc
    awk '{ print $6;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 -p1 > NC_fSt5Alp2l.txt;
    
    #tmIndex
    awk '{ print $1;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 -p1 > tmIndex.txt

    paste tmIndex.txt AmplitudeSt5Alp2l.txt > AmplitudeSt5Alp2.txt;
    paste tmIndex.txt NC_fSt5Alp2l.txt > NC_fSt5Alp2.txt;

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "5sts2alp-MonteCarlo.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75 
    set xrange [0:590490000000000]
    set yrange [0:1]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "#State=5, #Alphabet=2 TM 0 to 590490000000000 Monte Carlo"
    set datafile separator "\t"
    ntics = 20
    stats 'AmplitudeSt5Alp2.txt' using 1 name 'x' nooutput
    set xtics int(x_max/ntics)
    set style fill transparent solid 0.4 noborder
    plot "AmplitudeSt5Alp2.txt" using 1:2 with boxes linecolor '#CFB53B' title "Amplitude of Tape", "NC_fSt5Alp2.txt" using 1:2  with boxes linecolor '#4169E1' title "Normalized Compression"
EOF
    mv  5sts2alp-MonteCarlo.pdf ../resultPlots;
    rm  AmplitudeSt5Alp2.txt NC_fSt5Alp2.txt NC_fSt5Alp2l.txt AmplitudeSt5Alp2l.txt tmIndex.txt;
    rm  $results;
    cd ../scripts;
fi

# =======================================================================================
# Process Results of 6 state Turing Machines and 2 alphabet letters Monte Carlo Algorithm
# =======================================================================================

if [[ "$STATE6_ALPH2_TMs" -eq "1" ]];
    then
    cd ../resultText;
    echo "Creating plot of of all TM with #Alphabet=2, #States=6 Monte Carlo... ";
    
    var="6sts2alp";
    text=${var}.txt;
    results=${var}Results.txt;

    # tail -n +4 $text | head -n -3 | sort -k1 -n > new;
    # mv new $text
    
    < $text ../ioStNormalize $text > $results;
    
    #Amplitude
    awk '{ print $4;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 -p1> AmplitudeSt6Alp2l.txt; 
    
    #nc
    awk '{ print $6;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 -p1 > NC_fSt6Alp2l.txt;
    
    #tmIndex
    awk '{ print $1;}' $results | ../goose/bin/goose-filter -w 80001 -d 10000 -1 -p1 > tmIndex.txt

    paste tmIndex.txt AmplitudeSt6Alp2l.txt > AmplitudeSt6Alp2.txt;
    paste tmIndex.txt NC_fSt6Alp2l.txt > NC_fSt6Alp2.txt;

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "6sts2alp-MonteCarlo.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75 
    set xrange [0:4738381338321616896]
    set yrange [0:1]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "#State=6, #Alphabet=2 TM 0 to 4738381338321616896 Monte Carlo"
    set datafile separator "\t"
    ntics = 20
    stats 'AmplitudeSt6Alp2.txt' using 1 name 'x' nooutput
    set xtics int(x_max/ntics)
    set style fill transparent solid 0.4 noborder
    plot "AmplitudeSt6Alp2.txt" using 1:2 with boxes linecolor '#CFB53B' title "Amplitude of Tape", "NC_fSt6Alp2.txt" using 1:2  with boxes linecolor '#4169E1' title "Normalized Compression"
EOF
    mv  6sts2alp-MonteCarlo.pdf ../resultPlots;
    rm  AmplitudeSt6Alp2.txt NC_fSt6Alp2.txt NC_fSt6Alp2l.txt AmplitudeSt6Alp2l.txt tmIndex.txt;
    rm  $results;
    cd ../scripts;
fi


