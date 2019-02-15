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
    cat zzz | while read i; 
    do echo "scale = 10; $i/($maxnum * 0.5) " | bc; 
    done > zzz2
    cat zzz2 | ./goose/bin/goose-filter -w 201 -d 5 -1 -p1 > SC_f.txt
    

    tail -n +4 NC2st | head -n -3 | awk '{ print $4;}'| ./goose/bin/goose-filter -w 201 -d 5 -1 -p1 > NC_f.txt

    gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "Overlap.pdf"
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
    set format '%g'
    set xlabel "2 state Turing Machines 0 to 20736"
    set datafile separator "\t"
    unset xtics
    set style fill transparent solid 0.5 noborder
    plot "NC_f.txt" using 1 with boxes linecolor '#3D9970' title "Self-Compressor", "SC_f.txt" using 1 with boxes linecolor '#4169E1' title "Normalized Compression"
EOF
mv Overlap.pdf ./results
rm SC_f.txt zzz zzz2 NC_f.txt
fi


# ==============================================================================
# Process Results of 3 state Turing Machines
# ==============================================================================

#todo