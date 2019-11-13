#!/bin/bash
#

file=

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set size 0.98,1
    set output "${pdfFile}"
    set boxwidth 1
    set size ratio 0.6
    
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:100] 
    set yrange [1:${a}]
    set zrange [0:1.1]
    set cbrange [0:1]

    set grid xtics lt -1 
    set grid ytics lt -1
    set grid ztics lt -1
    set grid cbtics lt -1
    set border 3 front ls 101    
    
    set yzeroaxis lt 1 lw 2 lc rgb "black"
    set xzeroaxis lt 1 lw 2 lc rgb "black"

    set xyplane 0
    set logscale y 2
    set view 60,10
    set xlabel "Percentage of Substitutions \n to Fixed Nucleotide" rotate parallel font "Verdana-Bold,10" offset 0,-1,0
    set ylabel "Number of Blocks \n\n Permuted" rotate parallel font "Verdana-Bold,10" offset 0
    set zlabel "Normalized Compression" rotate parallel font "Verdana-Bold,10" offset -2
    set cblabel 'NC Variation' font "Verdana-Bold,10"
    set xtics font "Verdana-Bold,10" offset 0,-1,0
    set ztics font "Verdana-Bold,10" offset -1
    set ytics font "Verdana-Bold,9" offset -1
    set cbtics font "Verdana-Bold,10" offset -1
    set datafile separator "\t"
    set palette defined (0 "#0048ff",30 "#00ffff",55 "#ffff00", 70 "#ffcc00",90 "#ff8000",100 "#ff0000",101 "#b50000") 
    set title noenhanced
    set title "${title} \n NC variation with Edition and Permutation" font "Verdana-Bold,12"
    splot "${filename2}"  with pm3d notitle

EOF

