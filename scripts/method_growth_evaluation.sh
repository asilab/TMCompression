#!/bin/bash
#
#################################################
file="MethodIIGrowth";
file2="MethodIIIGrowth"; #Change
tail -n +2 ../resultText/$file > A;
tail -n +2 ../resultText/$file2 > B; 
../ioGrowthAverage A > "Average_"$file;
../ioGrowthAverage B > "Average_"$file2;
< Average_MethodIIGrowth awk '{ print $1,"\t",$2}' > Amplitude_m2;
< Average_MethodIIIGrowth awk '{ print $1,"\t",$2}' > Amplitude_m3;
< Average_MethodIIGrowth awk '{ print $1,"\t",$3}' > Bits_m2;
< Average_MethodIIIGrowth awk '{ print $1,"\t",$3}' > Bits_m3;
< Average_MethodIIGrowth awk '{ print $1,"\t",$4}' > NC_m2;
< Average_MethodIIIGrowth awk '{ print $1,"\t",$4}' > NC_m3;



gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "Growth_Amplitude.pdf"
    set style line 1 lt rgb "red" lw 3
    set xrange [0:990]
    set yrange [0:5000]
    set key left top
    set grid ytics lt -1
    set style fill solid
    set xlabel "Normalized Compression"
    set ylabel "Number iterations"
    set datafile separator "\t"
    set xtics
    set style fill transparent solid 0.5 noborder
    plot 'Amplitude_m2' using 1:2 linecolor '#4169E1' pointtype 7  pointsize 0.5 lw 0.5 title "TM tape average size with iterations - Method 2" ,\
    'Amplitude_m3' using 1:2 linecolor '#41A317' pointtype 7  pointsize 0.5 lw 0.5 title "TM tape average size with iterations - Method 3"
EOF


gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "Growth_Bits.pdf"
    set style line 1 lt rgb "red" lw 3
    set xrange [0:990]
    set yrange [0:300]
    set key left top
    set grid ytics lt -1
    set style fill solid
    set xlabel "Bits"
    set ylabel "Number iterations"
    set datafile separator "\t"
    set xtics
    set style fill transparent solid 0.5 noborder
    plot 'Bits_m2' using 1:2 linecolor '#4169E1' pointtype 7  pointsize 0.5 lw 0.5 title "TM tape average bits with iterations - Method 2" ,\
    'Bits_m3' using 1:2 linecolor '#41A317' pointtype 7  pointsize 0.5 lw 0.5 title "TM tape average bits with iterations - Method 3"
EOF


gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "Growth_NC.pdf"
    set style line 1 lt rgb "red" lw 3
    set xrange [0:990]
    set yrange [0:1]
    set key left top
    set grid ytics lt -1
    set style fill solid
    set xlabel "Normalized Compression"
    set ylabel "Number iterations"
    set datafile separator "\t"
    set xtics
    set style fill transparent solid 0.5 noborder
    plot 'NC_m2' using 1:2 linecolor '#4169E1' pointtype 7  pointsize 0.5 lw 0.5 title "TM tape average NC with iterations - Method 2" ,\
    'NC_m3' using 1:2 linecolor '#41A317' pointtype 7  pointsize 0.5 lw 0.5 title "TM tape average NC with iterations - Method 3"
EOF

pdfunite Growth_*.pdf Growth.pdf;
rm Growth_*.pdf;
rm A B Amplitude_m2 Amplitude_m3 NC_m2 NC_m3 Bits_m2 Bits_m3;