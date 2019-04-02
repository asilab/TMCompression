#!/bin/bash
#

echo "Recreating plots";

# ==============================================================================
# Profile of TM in provided file
# ==============================================================================

../tm --brief --profile -s 2 -a 2 -i 50000 -k 2 -t 4631 > profile4631.txt;
../tm --brief --profile -s 2 -a 3 -i 50000 -k 3 -t 32263324 > profile32263324.txt;
../tm --brief --profile -s 3 -a 2 -i 50000 -k 2 -t 21457002 > profile21457002.txt;
../tm --brief --profile -s 4 -a 2 -i 50000 -k 5 -t 74209803023 > profile74209803023.txt;
../tm --brief --profile -s 5 -a 2 -i 50000 -k 4 -t 252090028326298 > profile252090028326298.txt;
../tm --brief --profile -s 6 -a 2 -i 50000 -k 4 -t 191808832736487162 > profile191808832736487162.txt;

tail -n +3 profile4631.txt | awk '{ print $4;}' > nc_profile4631.txt;
tail -n +3 profile4631.txt | awk '{ print $2;}' > amp_profile4631.txt;
paste amp_profile4631.txt nc_profile4631.txt > profile4631.txt;

tail -n +3 profile32263324.txt | awk '{ print $4;}' > nc_profile32263324.txt;
tail -n +3 profile32263324.txt | awk '{ print $2;}' > amp_profile32263324.txt;
paste amp_profile32263324.txt nc_profile32263324.txt > profile32263324.txt;

tail -n +3 profile21457002.txt | awk '{ print $4;}' > nc_profile21457002.txt;
tail -n +3 profile21457002.txt | awk '{ print $2;}' > amp_profile21457002.txt;
paste amp_profile21457002.txt nc_profile21457002.txt > profile21457002.txt;

tail -n +3 profile74209803023.txt | awk '{ print $4;}' > nc_profile74209803023.txt;
tail -n +3 profile74209803023.txt | awk '{ print $2;}' > amp_profile74209803023.txt;
paste amp_profile74209803023.txt nc_profile74209803023.txt > profile74209803023.txt;

tail -n +3 profile252090028326298.txt | awk '{ print $4;}' > nc_profile252090028326298.txt;
tail -n +3 profile252090028326298.txt | awk '{ print $2;}' > amp_profile252090028326298.txt;
paste amp_profile252090028326298.txt nc_profile252090028326298.txt > profile252090028326298.txt;

tail -n +3 profile191808832736487162.txt | awk '{ print $4;}' > nc_profile191808832736487162.txt;
tail -n +3 profile191808832736487162.txt | awk '{ print $2;}' > amp_profile191808832736487162.txt;
paste amp_profile191808832736487162.txt nc_profile191808832736487162.txt > profile191808832736487162.txt;

rm amp_profile4631.txt nc_profile4631.txt;
rm amp_profile32263324.txt nc_profile32263324.txt;
rm amp_profile21457002.txt nc_profile21457002.txt;
rm amp_profile74209803023.txt nc_profile74209803023.txt;
rm amp_profile252090028326298.txt nc_profile252090028326298.txt;
rm amp_profile191808832736487162.txt nc_profile191808832736487162.txt;

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "NormalProfilesArticle.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:]
    set yrange [0:0.1]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 4"
    set xlabel "Amplitude of Tape"
    set ylabel "Normalized Compression"
    set datafile separator "\t"
    set style line 1 \
    linetype 1 linewidth 3 \
    pointtype 7 pointsize 0.01
    set style fill transparent solid 0.4 noborder
    plot "profile4631.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#0060ad' title "Tape 4631, #Q=2, #{/Symbol S}=2", \
    "profile32263324.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#7cf251' title "Tape 32263324, #Q=2, #{/Symbol S}=3", \
    "profile21457002.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#ffbf00' title "Tape 21457002, #Q=3, #{/Symbol S}=2", \
    "profile74209803023.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#ff7651' title "Tape 74209803023, #Q=4, #{/Symbol S}=2", \
    "profile252090028326298.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#ff7700' title "Tape 252090028326298, #Q=5, #{/Symbol S}=2", \
    "profile191808832736487162.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#ff0000' title "Tape 191808832736487162, #Q=6, #{/Symbol S}=2"

EOF
rm profile4631.txt profile32263324.txt profile21457002.txt profile74209803023.txt profile252090028326298.txt profile191808832736487162.txt;




# ==============================================================================
# Dynamical Profile of TM in provided file
# ==============================================================================

../tm --brief --dynprofile -s 2 -a 2 -i 50000 -k 2 -t 4631 > profile4631.txt;
../tm --brief --dynprofile -s 2 -a 3 -i 50000 -k 3 -t 32263324 > profile32263324.txt;
../tm --brief --dynprofile -s 3 -a 2 -i 50000 -k 2 -t 21457002 > profile21457002.txt;
../tm --brief --dynprofile -s 4 -a 2 -i 50000 -k 5 -t 74209803023 > profile74209803023.txt;
../tm --brief --dynprofile -s 5 -a 2 -i 50000 -k 4 -t 252090028326298 > profile252090028326298.txt;
../tm --brief --dynprofile -s 6 -a 2 -i 50000 -k 4 -t 191808832736487162 > profile191808832736487162.txt;

tail -n +3 profile4631.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 20 -d 80 -1 > nc_profile4631.txt;
tail -n +3 profile4631.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 20 -d 80 -1 > amp_profile4631.txt;
paste amp_profile4631.txt nc_profile4631.txt > profile4631.txt;

tail -n +3 profile32263324.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 20 -d 80 -1 > nc_profile32263324.txt;
tail -n +3 profile32263324.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 20 -d 80 -1 > amp_profile32263324.txt;
paste amp_profile32263324.txt nc_profile32263324.txt > profile32263324.txt;

tail -n +3 profile21457002.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 20 -d 80 -1 > nc_profile21457002.txt;
tail -n +3 profile21457002.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 20 -d 80 -1 > amp_profile21457002.txt;
paste amp_profile21457002.txt nc_profile21457002.txt > profile21457002.txt;

tail -n +3 profile74209803023.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 20 -d 80 -1 > nc_profile74209803023.txt;
tail -n +3 profile74209803023.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 20 -d 80 -1 > amp_profile74209803023.txt;
paste amp_profile74209803023.txt nc_profile74209803023.txt > profile74209803023.txt;

tail -n +3 profile252090028326298.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 20 -d 80 -1 > nc_profile252090028326298.txt;
tail -n +3 profile252090028326298.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 20 -d 80 -1 > amp_profile252090028326298.txt;
paste amp_profile252090028326298.txt nc_profile252090028326298.txt > profile252090028326298.txt;

tail -n +3 profile191808832736487162.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 20 -d 80 -1 > nc_profile191808832736487162.txt;
tail -n +3 profile191808832736487162.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 20 -d 80 -1 > amp_profile191808832736487162.txt;
paste amp_profile191808832736487162.txt nc_profile191808832736487162.txt > profile191808832736487162.txt;

rm amp_profile4631.txt nc_profile4631.txt;
rm amp_profile32263324.txt nc_profile32263324.txt;
rm amp_profile21457002.txt nc_profile21457002.txt;
rm amp_profile74209803023.txt nc_profile74209803023.txt;
rm amp_profile252090028326298.txt nc_profile252090028326298.txt;
rm amp_profile191808832736487162.txt nc_profile191808832736487162.txt;

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "DynamicProfilesArticle.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:]
    set yrange [0:1]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 4"
    set xlabel "Amplitude of Tape"
    set ylabel "Normalized Compression"
    set datafile separator "\t"
    set style line 1 \
    linetype 1 linewidth 3 \
    pointtype 7 pointsize 0.01
    plot "profile4631.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#0060ad' title "Tape 4631, #Q=2, #{/Symbol S}=2", \
    "profile21457002.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#ffbf00' title "Tape 21457002, #Q=3, #{/Symbol S}=2", \
    "profile32263324.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#7cf251' title "Tape 32263324, #Q=2, #{/Symbol f}=3", \
    "profile74209803023.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#ff7651' title "Tape 74209803023, #Q=4, #{/Symbol S}=2", \
    "profile252090028326298.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#ff7700' title "Tape 252090028326298, #Q=5, #{/Symbol S}=2", \
    "profile191808832736487162.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#ff0000' title "Tape 191808832736487162, #Q=6, #{/Symbol S}=2"

EOF
rm profile4631.txt profile21457002.txt profile74209803023.txt profile252090028326298.txt profile191808832736487162.txt;
mv DynamicProfilesArticle.pdf ../profiles;
mv NormalProfilesArticle.pdf ../profiles;
rm profile32263324.txt 