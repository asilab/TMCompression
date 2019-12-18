#!/bin/bash
#

#==============================================================================
#   Variables
#==============================================================================
INIT2st2="5000";
INITst2="14500";
ENDst2="17500";
#==============================================================================
INIT2st2alp3="9500000";
INITst2alp3="27000000";
ENDst2alp3="28500000";
#==============================================================================
INIT2st3="7500000";
INITst3="28000000";
ENDst3="30000000";
#==============================================================================
INIT2st4="20000000000";
INITst4="95000000000";
ENDst4="105000000000";
#==============================================================================
INIT2st5="8000000000000";
INITst5="530000000000000";
ENDst5="550000000000000";
#==============================================================================
INIT2st6="500000000000000000";
INITst6="4350000000000000000";
ENDst6="4450000000000000000";

#==============================================================================
#   Extract
#==============================================================================
< ../resultText/2sts2alp.txt awk -v b="$INITst2" -v e="$ENDst2" ' {if ( $1 >= b && $1 <= e ) print $1,$4,$5,$6 }'> Region2sts2alph.txt;
a=$(wc -l Region2sts2alph.txt | awk '{print $1}');
shuf -n $a ../resultText/2sts2alp.txt | awk -v a="$INIT2st2" -v b="$INITst2" -v e="$ENDst2" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1,$4,$5,$6 }' > Region_Outside_2sts2alph.txt;

< ../resultText/2sts3alp.txt awk -v b="$INITst2alp3" -v e="$ENDst2alp3" ' {if ( $1 >= b && $1 <= e ) print $1,$4,$5,$6}' > Region2sts3alph.txt;
a=$(wc -l Region2sts3alph.txt | awk '{print $1}');
shuf -n $a ../resultText/2sts3alp.txt | awk -v a="$INIT2st2alp3" -v b="$INITst2alp3" -v e="$ENDst2alp3" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1,$4,$5,$6 }' > Region_Outside_2sts3alph.txt;

< ../resultText/3sts2alp.txt  awk -v b="$INITst3" -v e="$ENDst3" ' {if ( $1 >= b && $1 <= e ) print $1,$4,$5,$6}' > Region3sts2alph.txt;
a=$(wc -l Region3sts2alph.txt | awk '{print $1}');
shuf -n $a ../resultText/3sts2alp.txt | awk -v a="$INIT2st3" -v b="$INITst3" -v e="$ENDst3" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1,$4,$5,$6 }' > Region_Outside_3sts2alph.txt;

< ../resultText/4sts2alp.txt awk -v b="$INITst4" -v e="$ENDst4" ' {if ( $1 >= b && $1 <= e ) print $1,$4,$5,$6}' > Region4sts2alph.txt;
a=$(wc -l Region4sts2alph.txt | awk '{print $1}');
shuf -n $a ../resultText/4sts2alp.txt | awk -v a="$INIT2st4" -v b="$INITst4" -v e="$ENDst4" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1,$4,$5,$6 }' > Region_Outside_4sts2alph.txt;

< ../resultText/5sts2alp.txt awk -v b="$INITst5" -v e="$ENDst5" ' {if ( $1 >= b && $1 <= e ) print $1,$4,$5,$6}' > Region5sts2alph.txt;
a=$(wc -l Region5sts2alph.txt | awk '{print $1}');
shuf -n $a ../resultText/5sts2alp.txt | awk -v a="$INIT2st5" -v b="$INITst5" -v e="$ENDst5" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1,$4,$5,$6 }' > Region_Outside_5sts2alph.txt;

< ../resultText/6sts2alp.txt  awk -v b="$INITst6" -v e="$ENDst6" ' {if ( $1 >= b && $1 <= e ) print $1,$4,$5,$6}' > Region6sts2alph.txt;
a=$(wc -l Region6sts2alph.txt | awk '{print $1}');
shuf -n $a ../resultText/6sts2alp.txt | awk -v a="$INIT2st6" -v b="$INITst6" -v e="$ENDst6" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1,$4,$5,$6 }'> Region_Outside_6sts2alph.txt;

#==============================================================================
#   Average Results
#==============================================================================
file1="Region2sts2alph.txt";
file2="Region_Outside_2sts2alph.txt";

echo "2sts2alph";
../ioAverage $file1 > IN2sts2alph
../ioAverage $file2 > OUT2sts2alph

file1="Region2sts3alph.txt";
file2="Region_Outside_2sts3alph.txt";

echo "2sts3alph";
../ioAverage $file1 > IN2sts3alph
../ioAverage $file2 > OUT2sts3alph

file1="Region3sts2alph.txt";
file2="Region_Outside_3sts2alph.txt";

echo "3sts2alph";
../ioAverage $file1 > IN3sts2alph
../ioAverage $file2 > OUT3sts2alph

file1="Region4sts2alph.txt";
file2="Region_Outside_4sts2alph.txt";

echo "4sts2alph";
../ioAverage $file1 > IN4sts2alph
../ioAverage $file2 > OUT4sts2alph

file1="Region5sts2alph.txt";
file2="Region_Outside_5sts2alph.txt";

echo "5sts2alph";
../ioAverage $file1 > IN5sts2alph
../ioAverage $file2 > OUT5sts2alph

file1="Region6sts2alph.txt";
file2="Region_Outside_6sts2alph.txt";

echo "6sts2alph";
../ioAverage $file1 > IN6sts2alph
../ioAverage $file2 > OUT6sts2alph


printf "1\n3\n5\n7\n9\n11" > Index1;
printf "2\n4\n6\n8\n10\n12"> Index2;
cat IN2sts2alph IN2sts3alph IN3sts2alph IN4sts2alph IN5sts2alph IN6sts2alph > IN1;
cat OUT2sts3alph OUT2sts3alph OUT3sts2alph OUT4sts2alph OUT5sts2alph OUT6sts2alph > OUT1;
paste Index1 IN1 > IN;
paste Index2 OUT1 > OUT;

rm Index1 Index2;
#==============================================================================
#   Plots
#==============================================================================


< IN  awk '{print $1,"\t",$2}' > AMPIN;
< OUT awk '{print $1,"\t",$2}' > AMPOUT;

< IN  awk '{print $1,"\t",$3}' > SCIN;
< OUT awk '{print $1,"\t",$3}' > SCOUT;

< IN awk '{print $1,"\t",$4}' > NCIN;
< OUT awk '{print $1,"\t",$4}' > NCOUT;

rm OUT* IN*

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "AMP.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:13]
    set yrange [0:]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel  "Inside, Outside"
    set ylabel "Amplitude"
    set datafile separator "\t"
    plot "AMPIN" using 1:2 with boxes linecolor '#41A317' title "Inside Region",\
    "AMPOUT" using 1:2 with boxes linecolor '#E41B17' title "Outside Region"
EOF

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "SC.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:13]
    set yrange [0:]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel  "Inside, Outside"
    set ylabel "Bits Required"
    set datafile separator "\t"
    plot "SCIN" using 1:2 with boxes linecolor '#41A317' title "Inside Region",\
    "SCOUT" using 1:2 with boxes linecolor '#E41B17' title "Outside Region"
EOF


gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "NC.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:13]
    set yrange [0:1]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "Inside, Outside"
    set ylabel "Normalized Compression"
    set datafile separator "\t"
    plot "NCIN" using 1:2 with boxes linecolor '#41A317' title "Inside Region",\
    "NCOUT" using 1:2 with boxes linecolor '#E41B17' title "Outside Region"
EOF
#==============================================================================
#   Remove
#==============================================================================

pdfunite AMP.pdf SC.pdf NC.pdf AverageInsidevsOutsideTape.pdf;
mv AverageInsidevsOUtside.pdf ../resultPlots/
rm AMP* NC* SC* Index* Region*
