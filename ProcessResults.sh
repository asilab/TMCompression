#!/bin/bash
#
# ==============================================================================
# Options
# ==============================================================================
INSTALL_GOOSE=0;
NC_2STATE_TM=1;
SC_2STATE_TM=1;
NC_3STATE_TM=0;
SC_3STATE_TM=0;
# ==============================================================================
# Install BDM
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
# Process Results of 2 state Turing Machines
# ==============================================================================
# Self-Compression
# ==============================================================================
if [[ "$SC_2STATE_TM" -eq "1" ]];
    then
    tail -n +4 SelfCompr | head -n -3 | awk '{ print $4;}'> zzz; 
    
    maxnum=$(sort -n zzz |tail -1)   
    cat zzz | while read i; do echo "scale = 10; $i/$maxnum" | bc; done | ./goose/bin/goose-filter -w 201 -d 5 -1 -p1 > SC_f.txt
    gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "SC_AVG_2State_TM.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:]
    set yrange [:]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set ylabel "Self-Compression"
    set format '%g'
    set xlabel "2 state Turing Machines 0 to 20736"
    set datafile separator "\t"
    unset xtics 
    plot "SC_f.txt" using 1 with boxes linecolor '#3D9970' title "Average Compressibility Compressor"
EOF
mv SC_AVG_2State_TM.pdf ./results
rm SC_f.txt
fi

# ==============================================================================
# Normalized Compression
# ==============================================================================

if [[ "$NC_2STATE_TM" -eq "1" ]];
    then
    tail -n +4 NC2stateTM | head -n -3 | awk '{ print $4;}'| ./goose/bin/goose-filter -w 201 -d 5 -1 -p1 > NC_f.txt
    
    gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "NC_AVG_2State_TM.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:]
    set yrange [:]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set ylabel "Normalized Compression"
    set format '%g'
    set xlabel "2 state Turing Machines 0 to 20736"
    set datafile separator "\t"
    unset xtics 
    plot "NC_f.txt" using 1 with boxes linecolor '#3D9970' title "Average Compressibility Compressor"
EOF
mv NC_AVG_2State_TM.pdf ./results
rm NC_f.txt
fi



# ==============================================================================
# Process Results of 3 state Turing Machines
# ==============================================================================

#todo