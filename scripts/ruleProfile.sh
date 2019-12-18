#!/bin/bash
#
if [ $# -ne 5 ]; then
    echo "Not enough arguments arguments provided, you need to provide 5 arguments:";
    echo "All args are numbers required for the creation of the TM dynamical profile";
    echo "";
    echo "Arg[1]: TM index Number";
    echo "Arg[2]: TM #States";
    echo "Arg[3]: TM #Alphabet";
    echo "Arg[4]: TM Number Iterations";
    echo "Arg[5]: TM k Number";
    exit 1;
fi

# ==============================================================================
# Variables
# ==============================================================================

Machine=$1;
txtName=rule_profile${1}.txt;
pdfName=rule_profile${1}.pdf;
SavePath="../profiles/";
STATE=$2;
ALPHABET=$3;
NUMBERITERATION=$4;
K=$5;

# ==============================================================================
# Create Folder
# ==============================================================================

Folder=${STATE}St${ALPHABET}AlphTM/;
DIRECTORY=${SavePath}${Folder};

if [ ! -d "$DIRECTORY" ]; 
    then
    cd $SavePath;
    mkdir $Folder;
    cd ..;
fi

# ==============================================================================
# Rule profile curves of Turing Machines
# ==============================================================================

../tm --brief --ruleProfile -s $STATE -a $ALPHABET -i $NUMBERITERATION -k $K -t $Machine > $txtName;
tail -n +3 $txtName | awk '{ print $4;}' > nc_profile.txt;
tail -n +3 $txtName | awk '{ print $2;}' > amp_profile.txt;
paste amp_profile.txt nc_profile.txt > profile.txt;

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
    set ylabel "Compression Profile"
    set datafile separator "\t"
    set style line 1 \
    linecolor rgb '#0060ad' \
    linetype 1 linewidth 3 \
    pointtype 7 pointsize 0.01
    plot "profile.txt" using 1:2 with linespoints linestyle 1 title "NC Profile of Tape $Machine"
EOF

mv profile.pdf $pdfName;
mv $pdfName $DIRECTORY;
rm nc_profile.txt amp_profile.txt profile.txt $txtName;