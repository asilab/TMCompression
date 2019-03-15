#!/bin/bash
#

if [ $# -ne 3 ]; then
    echo "Not enough arguments arguments provided, you need to provide 3 arguments:";
    echo "All args are boolean (0 or 1)";
    echo "";
    echo "Arg[0]: Install AC";
    echo "Arg[2]: Validate TM Tapes";
    echo "Arg[3]: Validate Profile with Compression AC";
    exit 1;
fi

# ==============================================================================
# Options
# ==============================================================================
INSTALL_AC=$1;
VAL_TAPES=$2;
TEST_CMP=$3;
ITERATION=50000;
# ==============================================================================
# Install AC
# ==============================================================================
if [[ "$INSTALL_AC" -eq "1" ]];
    then
    git clone https://github.com/pratas/ac.git
    cd ac/src/
    cmake .
    make
    cp AC ../../
    cd ../../
fi
# ==============================================================================
# Validate TM Tapes
# ==============================================================================
if [[ "$VAL_TAPES" -eq "1" ]];
    then
    ./tm --brief --StMatrix -s 2 -a 3 -t 15571925
    ./tm --brief --printTape -s 2 -a 3 -i 101 -t 15571925 > Tape1.txt;
    sed -i 's/[^0-9]*//g' Tape1.txt;

    ./TMsimulator 2 3 100 12542675 12542675 | head -n +12;
    ./TMsimulator 2 3 100 12542675 12542675| grep "tape">Tape1val.txt;
    sed -i 's/[^0-9]*//g' Tape1val.txt;
    cmp Tape1.txt Tape1val.txt;
    #==============
    ./tm --brief --StMatrix -s 2 -a 3 -t 15571907
    ./tm --brief --printTape -s 2 -a 3 -i 101 -t 15571907 > Tape1.txt;
    sed -i 's/[^0-9]*//g' Tape1.txt;

    ./TMsimulator 2 3 100 12542674 12542674 | head -n +12;
    ./TMsimulator 2 3 100 12542674 12542674 | grep "tape" >Tape1val.txt;
    sed -i 's/[^0-9]*//g' Tape1val.txt;
    cmp Tape1.txt Tape1val.txt;
   #===============
    ./tm --brief --StMatrix -s 2 -a 3 -t 32438743
    ./tm --brief --printTape -s 2 -a 3 -i 101 -t 32438743 > Tape1.txt;
    sed -i 's/[^0-9]*//g' Tape1.txt;

    ./TMsimulator 2 3 100 16078 16078 | head -n +12;
    ./TMsimulator 2 3 100 16078 16078 | grep "tape" >Tape1val.txt;
    sed -i 's/[^0-9]*//g' Tape1val.txt;
    cmp Tape1.txt Tape1val.txt;
    #===============
    ./tm --brief --StMatrix -s 2 -a 3 -t 19311563
    ./tm --brief --printTape -s 2 -a 3 -i 101 -t 19311563 > Tape1.txt;
    sed -i 's/[^0-9]*//g' Tape1.txt;
    
    ./TMsimulator 2 3 100 11542228 11542228 | head -n +12;
    ./TMsimulator 2 3 100 11542228 11542228 | grep "tape" >Tape1val.txt;
    sed -i 's/[^0-9]*//g' Tape1val.txt;
    cmp Tape1.txt Tape1val.txt

fi


# ==============================================================================
# Validate Profile Compression AC
# ==============================================================================
#

if [[ "$TEST_CMP" -eq "1" ]];
    then

    tail -n +4 3st.txt | head -n -3 | sort -k 6,6 |awk '$4 < 100 { next } { print }' | tail -n 50 | awk ' { print $1}' > InterestingMachines.txt;

    while read p; do
        txtName=ACProfile${p}.txt;
        PdfName=ACProfile${p}.pdf;
        SavePath="./profiles/3st/AC/"; # Change this path
        ./tm --brief --printTape -s 3 -a 2 -i $ITERATION -t $p > tape.txt;
        tr -d -c "01" < tape.txt > tape_clean.txt;
        ./AC -v -e -tm 3:1:0.9/0:0:0 tape_clean.txt;
        mv tape_clean.txt.iae profile.txt;
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
            set yrange [0:0.5]
            set border 3 front ls 101
            set grid ytics lt -1
            set style fill solid
            set format '%g'
            set xtics font ", 4"
            set xlabel "Amplitude of Tape"
            set ylabel "Normalized Compression"
            set datafile separator "\t"
            plot "profile.txt" using 1 linecolor '#4169E1' pointtype 7 pointsize 0.5 lw 0.5 title "NC Profile of Tape"
EOF
    mv profile.pdf $PdfName;
    mv $PdfName $SavePath;
    mv $txtName $SavePath;
    done < InterestingMachines.txt
fi

# ==============================================================================
# Other validations
# ==============================================================================