#!/bin/bash
#
file=$1;
function avg {
    count=0;
    total=0;

    for i in $( awk '{ print $1; }' $1 )
    do 
        total=$(echo $total+$i | bc )
        ((count++))
    done
    echo "scale=4; $total / $count" | bc
}

for y in {1..200}
    do
        echo  ${y} >> index2;
done
					
tail -n +2 ../resultText/$file | awk '{ print $1;}' | ../goose/bin/goose-filter -w 4 -d 0 -1 > amp_ini;
tail -n +2 ../resultText/$file | awk '{ print $4;}' | ../goose/bin/goose-filter -w 4 -d 0 -1 > amp_fin;

tail -n +2 ../resultText/$file | awk '{ print $2;}' | ../goose/bin/goose-filter -w 4 -d 0 -1 > SC_ini;
tail -n +2 ../resultText/$file | awk '{ print $5;}'| ../goose/bin/goose-filter -w 4 -d 0 -1 > SC_fin;

tail -n +2 ../resultText/$file | awk '{ print $3;}' | ../goose/bin/goose-filter -w 4 -d 0 -1 > NC_ini;
tail -n +2 ../resultText/$file | awk '{ print $6;}'| ../goose/bin/goose-filter -w 4 -d 0 -1 > NC_fin;

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "amplitude_tm_evolve.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:200]
    set yrange [0:5000]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "TM 0-200"
    set ylabel "Amplitude"
    set datafile separator "\t"
    set style fill transparent solid 1.0
    plot "amp_ini" using 1:2 with boxes linecolor '#41A317' title "Initial Amplitude",\
    "amp_fin" using 1:2  with boxes linecolor '#E41B17' title "Final Amplitude"
EOF

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "SC_tm_evolve.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:200]
    set yrange [0:200]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "TM 0-200"
    set ylabel "Self Compression"
    set datafile separator "\t"
    set style fill transparent solid 1.0
    plot "SC_fin" using 1:2  with boxes linecolor '#E41B17' title "Final Compression" ,\
    "SC_ini" using 1:2 with boxes linecolor '#41A317' title "Initial Compression"
    
    
    
EOF

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "NC_tm_evolve.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:200]
    set yrange [0:1]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "TM 0-200"
    set ylabel "Normalized Compression"
    set datafile separator "\t"
    set style fill transparent solid 1.0
    plot "NC_fin" using 1:2  with boxes linecolor '#E41B17' title "Final NC",\
    "NC_ini" using 1:2 with boxes linecolor '#41A317' title "Initial NC"
    
EOF

rm amp_ini	SC_ini	NC_ini	amp_fin	SC_fin	NC_fin;
rm index2;



echo  1 >> index1;
echo  2 >> index2;


tail -n +2 ../resultText/$file | awk '{ print $1;}' >  amp_ini;
tail -n +2 ../resultText/$file | awk '{ print $4;}' > amp_fin;
avg amp_ini > A_ini_avg;
avg amp_fin > A_fin_avg;
paste index1 A_ini_avg > amp_ini_avg;
paste index2 A_fin_avg > amp_fin_avg ;

tail -n +2 ../resultText/$file | awk '{ print $2;}' > SC_ini;
tail -n +2 ../resultText/$file | awk '{ print $5;}' > SC_fin;
avg SC_ini > S_ini_avg;
avg SC_fin > S_fin_avg;
paste index1 S_ini_avg > SC_ini_avg;
paste index2 S_fin_avg > SC_fin_avg;

tail -n +2 ../resultText/$file | awk '{ print $3;}' > NC_ini;
tail -n +2 ../resultText/$file | awk '{ print $6;}' > NC_fin;
avg NC_ini > N_ini_avg;
avg NC_fin > N_fin_avg;
paste index1 N_ini_avg > NC_ini_avg;
paste index2 N_fin_avg > NC_fin_avg;

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "tm_amp_avg_evolve.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:3]
    set yrange [0:5000]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "TM Avg Before, After"
    set ylabel "Amplitude"
    set datafile separator "\t"
    plot "amp_ini_avg" using 1:2 with boxes linecolor '#41A317' title "Inicial Mean Amplitude",\
    "amp_fin_avg" using 1:2  with boxes linecolor '#E41B17' title "Final Mean Amplitude"
EOF

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "tm_sc_avg_evolve.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:3]
    set yrange [0:200]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "TM Avg Before, After"
    set ylabel "Self Compression"
    set datafile separator "\t"
    plot "SC_ini_avg" using 1:2 with boxes linecolor '#41A317' title "Inicial Mean Required bits",\
    "SC_fin_avg" using 1:2  with boxes linecolor '#E41B17' title "Final Mean Required bits"
EOF

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "tm_amp_nc_evolve.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:3]
    set yrange [0:1]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 6"
    set xlabel "TM Avg Before, After"
    set ylabel "Normalized Compression"
    set datafile separator "\t"
    plot "NC_ini_avg" using 1:2 with boxes linecolor '#41A317' title "Initial Mean NC",\
    "NC_fin_avg" using 1:2 with boxes linecolor '#E41B17' title "Final Mean NC"
EOF


rm index1 index2;
rm amp_ini	SC_ini	NC_ini	amp_fin	SC_fin	NC_fin;
rm *_avg;
pdfunite *_evolve.pdf ${1}".pdf"
mv ${1}".pdf" ../resultPlots/
rm *evolve.pdf;