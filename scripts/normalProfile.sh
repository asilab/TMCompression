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
    echo "Arg[4]: TM k Number";
    exit 1;
fi

# ==============================================================================
# Variables
# ==============================================================================

Machine=$1;
txtName=Profile${1}.txt;
pdfName=Profile${1}.pdf;
SavePath="./profiles/";
STATE=$2;
ALPHABET=$3;
NUMBERITERATION=$4;
K=$5;

# ==============================================================================
# Create Folder
# ==============================================================================

Folder=${STATE}St${ALPHABET}AlphTM/;
DIRECTORY=${SavePath}${Folder};

if [ -d "$DIRECTORY" ]; 
    then
    echo "this folder exists";
else
    cd $SavePath;
    mkdir $Folder;
    cd ..;
fi

# ==============================================================================
# Profile curves of Turing Machines
# ==============================================================================

./tm --brief --profile -s $STATE -a $ALPHABET -i $NUMBERITERATION -k $K -t $Machine > $txtName;
tail -n +3 $txtName | awk '{ print $4;}'  > nc_profile.txt;
tail -n +3 $txtName | awk '{ print $2;}'> amp_profile.txt;
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
    set ylabel "Normalized Compression"
    set datafile separator "\t"
    plot "profile.txt" using 1:2 linecolor '#4169E1' pointtype 7 pointsize 0.3 lw 0.5 title "NC Profile of Tape"
EOF

mv profile.pdf $pdfName;
mv $pdfName $DIRECTORY;
rm nc_profile.txt amp_profile.txt profile.txt $txtName;