if [ $# -eq 0 ]; then
    echo "No arguments provided"
    exit 1
fi

# ==============================================================================
# Variables
# ==============================================================================
Machine=$1;
txtName="Profile"$1".txt";
pdfName="Profile"$1".pdf";

SavePath="./Profiles/"$2"st"/

# ==============================================================================
# Pofile curves Results of 3 state Turing Machines
# ==============================================================================

./tm --brief --profile -s 2 -a 2 -i 50000 -k 2 -t $1 > $txtName;
tail -n +3 $txtName | awk '{ print $4;}'  > nc_profile.txt;
tail -n +3 $txtName | awk '{ print $2;}'> amp_profile.txt;
paste amp_profile.txt nc_profile.txt > profile.txt

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "profile.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:]
    set yrange [0:]
    set border 3 front ls 101
    set grid ytics lt -1
    set style fill solid
    set format '%g'
    set xtics font ", 4"
    set xlabel "Amplitude of Tape"
    set ylabel "Normalized Compression"
    set datafile separator "\t"
    plot "profile.txt" using 1:2 linecolor '#4169E1' pointtype 7 pointsize 0.3 lw 0.5 title "NC Profile of Tape"
EOF

mv profile.pdf $pdfName;
mv $pdfName $SavePath;
rm nc_profile.txt amp_profile.txt profile.txt $txtName;