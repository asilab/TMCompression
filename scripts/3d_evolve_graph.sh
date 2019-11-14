#!/bin/bash
#
file="Avg_results_tm_evolution.txt";
pdfFile1="NC.pdf";
pdfFile2="SC.pdf";
pdfFile3="Amplitude.pdf";


gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set size 0.98,1
    set output "${pdfFile1}"
    set boxwidth 1
    set size ratio 0.6
    
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [50:3200] 
    set yrange [500:8000]
    set zrange [0:0.41]
    set cbrange [0:0.4]

    set grid xtics lt -1 
    set grid ytics lt -1
    set grid ztics lt -1
    set grid cbtics lt -1
    set border 3 front ls 101    
    
    set yzeroaxis lt 1 lw 2 lc rgb "black"
    set xzeroaxis lt 1 lw 2 lc rgb "black"
    set view 50,10

    set xyplane 0
    set xlabel "Rule Iterations"  font "Verdana-Bold,10" rotate parallel 
    set ylabel "Tape Iterations" font "Verdana-Bold,10" rotate parallel offset -2
    set zlabel "Average \n NC Variation" font "Verdana-Bold,10" rotate parallel offset -4
    set cblabel 'NC Variation' font "Verdana-Bold,10" offset +2
    set xtics font "Verdana-Bold,10" 
    set ztics font "Verdana-Bold,10" 
    set ytics font "Verdana-Bold,9" offset -2
    set cbtics font "Verdana-Bold,10"
    set logscale x 2
    set datafile separator "\t"
    set palette defined (0 "#0048ff",30 "#00ffff",55 "#ffff00", 70 "#ffcc00",90 "#ff8000",100 "#ff0000",101 "#b50000"); 
    set title noenhanced
    splot "../resultText/${file}" using 1:2:5  with pm3d notitle

EOF

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set size 0.98,1
    set output "${pdfFile2}"
    set boxwidth 1
    set size ratio 0.6
    
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [50:3200] 
    set yrange [500:8000]
    set zrange [0:55]
    set cbrange [0:55]

    set grid xtics lt -1 
    set grid ytics lt -1
    set grid ztics lt -1
    set grid cbtics lt -1
    set border 3 front ls 101    
    
    set yzeroaxis lt 1 lw 2 lc rgb "black"
    set xzeroaxis lt 1 lw 2 lc rgb "black"
    set view 50,10

    set xyplane 0
    set xlabel "Rule Iterations"  font "Verdana-Bold,10" rotate parallel 
    set ylabel "Tape Iterations" font "Verdana-Bold,10" rotate parallel offset -2
    set zlabel "Average \n Required Bits" font "Verdana-Bold,10" rotate parallel offset -4
    set cblabel 'NC Variation' font "Verdana-Bold,10" offset +2
    set xtics font "Verdana-Bold,10" 
    set ztics font "Verdana-Bold,10" 
    set ytics font "Verdana-Bold,9" offset -2
    set cbtics font "Verdana-Bold,10"
    set logscale x 2

    set datafile separator "\t"
    set palette defined (0 "#0048ff",30 "#00ffff",55 "#ffff00", 70 "#ffcc00",90 "#ff8000",100 "#ff0000",101 "#b50000");     
    set title noenhanced
    splot "../resultText/${file}" using 1:2:4  with pm3d notitle

EOF
gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set size 0.98,1
    set output "${pdfFile3}"
    set boxwidth 1
    set size ratio 0.6
    
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [50:3200] 
    set yrange [500:8000]
    set zrange [0:3500]
    set cbrange [0:3500]

    set grid xtics lt -1 
    set grid ytics lt -1
    set grid ztics lt -1
    set grid cbtics lt -1
    set border 3 front ls 101    
    set logscale x 2

    set yzeroaxis lt 1 lw 2 lc rgb "black"
    set xzeroaxis lt 1 lw 2 lc rgb "black"
    set view 50,10

    set xyplane 0
    set xlabel "Rule Iterations"  font "Verdana-Bold,10" rotate parallel 
    set ylabel "Tape Iterations" font "Verdana-Bold,10" rotate parallel offset -2
    set zlabel "Average \n Final Amplitude" font "Verdana-Bold,10" rotate parallel offset -4
    set cblabel 'NC Variation' font "Verdana-Bold,10" offset +2
    set xtics font "Verdana-Bold,10" 
    set ztics font "Verdana-Bold,10" 
    set ytics font "Verdana-Bold,9" offset -2
    set cbtics font "Verdana-Bold,10"
    set datafile separator "\t"
    set palette defined (0 "#0048ff",30 "#00ffff",55 "#ffff00", 70 "#ffcc00",90 "#ff8000",100 "#ff0000",101 "#b50000")
     
    set title noenhanced
    splot "../resultText/${file}" using 1:2:3  with pm3d notitle

EOF
pdfunite NC.pdf SC.pdf Amplitude.pdf avg_tm_improve_results.pdf;
mv avg_tm_improve_results.pdf ../resultPlots/;
rm NC.pdf SC.pdf Amplitude.pdf;