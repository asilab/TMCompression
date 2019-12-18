#!/bin/bash
#
if [ $# -ne 4 ]; then
    echo "Not enough arguments arguments provided, you need to provide 3 arguments:";
    echo "All args are boolean (0 or 1)";
    echo "";
    echo "If 1st Argument == 1: Install requirements for bdm";
    echo "bash bdm_NC_comparisson.sh 1 0 0 0";
    echo "If 2nd Argument == 1: Get 10k elements";
    echo "bash bdm_NC_comparisson.sh 0 1 0 0";
    echo "If 3rd Argument == 1: Compute bdm";
    echo "bash bdm_NC_comparisson.sh 0 0 1 0";
    echo "If 4th Argument == 1: Plots bdm vs NC";
    echo "bash bdm_NC_comparisson.sh 0 0 0 1";
    echo "";
    exit 1;
fi
#==============================================================================
#   Variables
#==============================================================================
# ==============================================================================
# Variables
# ==============================================================================
REQUIREMENTS=$1;
SHUFLE=$2;
BDM=$3;
PLOT=$4;
# Default Variables

# listar n de 10 k : 10 / 8 / 6 estados. 5000 it
# fazer grafico 
# calcular bdm
# ==============================================================================
# Installing Requirements
# ==============================================================================

if [[ "$REQUIREMENTS" -eq "1" ]];
    then

    echo "This task in specific use the BDM Python3 API, make sure you have it available as well as pip...";
    pip install git+https://github.com/sztal/pybdm.git
    pip install numpy

fi

# ==============================================================================
# Get 10k results from 10, 8 and 6 states and a binary alphabet
# ==============================================================================

if [[ "$SHUFLE" -eq "1" ]];
    then
    cd ../resultText;
    shuf -n 10000 10st2alp-uint128.txt |  sort -k1 -n > 10k_10st_txt;
    shuf -n 10000 8st2alp-uint128.txt | sort -k1 -n > 10k_8st_txt;
    shuf -n 10000 resultText/6sts2alp.txt | sort -k1 -n > 10k_6st_txt;
    cd ../scripts;
fi

# ==============================================================================
# Compute BDM
# ==============================================================================
if [[ "$BDM" -eq "1" ]];
    then
    cd ../resultText;

    function getBDM {
        while read p; do
            ../tm --brief --printTape -s $2 -a $3 -i 50000 -t $p > Index_tape;
            a=`awk '{ print $1;}' Index_tape`;
            awk '{ print $2;}' Index_tape > tape;
            bdm=`python bdm.py tape`;
            if [ -z "$bdm" ]
            then
                bdm=0.0;
            fi
            echo -e $a'\t'$bdm;
        done < $1;
    }

    < 10k_10st_txt awk '{ print $1;}' > index10st;
    < 10k_8st_txt awk '{ print $1;}' > index8st;
    < 10k_6st_txt awk '{ print $1;}' > index6st;

    getBDM "index10st" 10 2 > 10k_10st_bdm.txt;
    getBDM "index8st" 8 2 > 10k_8st_bdm.txt; 
    getBDM "index6st" 6 2 > 10k_6st_bdm.txt; 
    
    rm index6st index8st index10st tape Index_tape;
    cd ../scripts;
fi
# ==============================================================================
# Plot
# ==============================================================================
function plot_bdm_nc_comp {
    #Amplitude
    awk '{ print $4;}' $1 | ../goose/bin/goose-filter -w 801 -d 10 -1 > Amplitude.txt; 
    #nc
    awk '{ print $6;}' $1 | ../goose/bin/goose-filter -w 801 -d 10 -1 > NC.txt;
    #bdm    
    awk '{print $7*100;}' $1 | ../goose/bin/goose-filter -w 801 -d 10 -1 > BDM.txt;
    
    gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "$4"
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
    set xtics font ", 6"
    set xlabel "10.000 Turing Machines #Q=${2}, #{/Symbol S}=${3}"
    set datafile separator "\t"
    ntics = 20
    stats 'Amplitude.txt' using 1 name 'x' nooutput
    set xtics int(x_max/ntics)
    set style fill solid 0.4 noborder
    plot "Amplitude.txt" using 1:2 with boxes linecolor '#CFB53B' title "Amplitude of Tape",\
    "NC.txt" using 1:2  with boxes linecolor '#4169E1' title "Normalized Compression",\
    "BDM.txt" using 1:2  with boxes linecolor '#E41B17' title "Block Decomposition Method x 100"
EOF
 rm Amplitude.txt NC.txt BDM.txt;
 mv $4 ../resultPlots
}

function plot_bdm_nc_comp2 {
    #Amplitude
    awk '{ print $4;}' $1 | ../goose/bin/goose-filter -w 801 -d 10 -1 > Amplitude.txt; 
    #nc
    awk '{ print $6;}' $1 | ../goose/bin/goose-filter -w 801 -d 10 -1 > NC.txt;
    #bdm    
    awk '{print $7}' $1 | ../goose/bin/goose-filter -w 20 -d 10 -1 > BDM.txt;
    
    gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "$4"
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
    set xtics font ", 6"
    set xlabel "10.000 Turing Machines #Q=${2}, #{/Symbol S}=${3}"
    set datafile separator "\t"
    ntics = 20
    stats 'Amplitude.txt' using 1 name 'x' nooutput
    set xtics int(x_max/ntics)
    set style fill solid 0.4 noborder
    plot "Amplitude.txt" using 1:2 with boxes linecolor '#CFB53B' title "Amplitude of Tape",\
    "NC.txt" using 1:2  with boxes linecolor '#4169E1' title "Normalized Compression",\
    "BDM.txt" using 1:2  with boxes linecolor '#E41B17' title "Block Decomposition Method"
EOF
 rm Amplitude.txt NC.txt BDM.txt;
 mv $4 ../resultPlots
}


if [[ "$PLOT" -eq "1" ]];
    then
    
    cd ../resultText;
    ../ioStNormalize 10k_10st_txt > NC_10k_10st.txt;
    ../ioStNormalize 10k_8st_txt > NC_10k_8st.txt;
    ../ioStNormalize 10k_6st_txt > NC_10k_6st.txt;
    

    awk '{ print $2;}' 10k_10st_bdm.txt > BDM;
    paste 10k_10st_txt BDM > AVGCOMPBDM;
    ../bdmAvg AVGCOMPBDM > AVGCOMPBDMNC;
    paste  NC_10k_10st.txt BDM > Comp_BDM_NC_AMP_10st.txt;
     

    awk '{ print $2;}' 10k_8st_bdm.txt > BDM;
    paste 10k_8st_txt BDM > AVGCOMPBDM;
    ../bdmAvg AVGCOMPBDM >> AVGCOMPBDMNC;
    paste  NC_10k_8st.txt BDM > Comp_BDM_NC_AMP_8st.txt;
    
    awk '{ print $2;}' 10k_6st_bdm.txt > BDM;
    paste 10k_6st_txt BDM > AVGCOMPBDM;
    ../bdmAvg AVGCOMPBDM >> AVGCOMPBDMNC;
    paste  NC_10k_6st.txt BDM > Comp_BDM_NC_AMP_6st.txt;

    plot_bdm_nc_comp Comp_BDM_NC_AMP_10st.txt 10 2 Comp_BDM_NC_AMP_10st.pdf
    plot_bdm_nc_comp2 Comp_BDM_NC_AMP_10st.txt 10 2 Comp_BDM_NC_AMP_10st_NO_Scalling.pdf
    plot_bdm_nc_comp Comp_BDM_NC_AMP_8st.txt 8 2 Comp_BDM_NC_AMP_8st.pdf
    plot_bdm_nc_comp Comp_BDM_NC_AMP_6st.txt 6 2 Comp_BDM_NC_AMP_6st.pdf

    rm BDM NC_10k_10st.txt NC_10k_8st.txt NC_10k_6st.txt AVGCOMPBDM;
    rm Comp_BDM_NC_AMP_10st.txt Comp_BDM_NC_AMP_8st.txt Comp_BDM_NC_AMP_6st.txt; 
    cd ../scripts;

fi