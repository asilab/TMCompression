#!/bin/bash
#
if [ $# -ne 5 ]; then
    echo "Not enough arguments arguments provided, you need to provide 3 arguments:";
    echo "All args are boolean (0 or 1)";
    echo "";
    echo "If 1st Argument == 1: Reproduce normal profile in article";
    echo "bash reprArticlePlot.sh.sh 1 0 0 0 0";
    echo "";
    echo "If 2nd Argument == 1:  Reproduce dynamic profile in article";
    echo "bash reprArticlePlot.sh.sh 0 1 0 0 0";
    echo "";
    echo "If 3nd Argument == 1:  Reproduce Edition String profile in article";
    echo "bash reprArticlePlot.sh.sh 0 0 1 0 0";
    echo "";
    echo "If 4nd Argument == 1:  Reproduce Edition/Permutation of Parvovirus Virus DNA sequence NC plot of the article";
    echo "bash reprArticlePlot.sh.sh 0 0 0 1 0";
    echo "";
    echo "If 4nd Argument == 1:  Reproduce Edition/Permutation of Herpes Virus DNA sequence NC plot of the article";
    echo "bash reprArticlePlot.sh.sh 0 0 0 0 1";
    echo "";
    exit 1;
fi

# ==============================================================================
# Variables
# ==============================================================================
NP=$1;
DP=$2;
NC=$3;
PVNC=$4;
HVNC=$5;

# ==============================================================================
# Profile of TM in provided file
# ==============================================================================
if [[ "$NP" -eq "1" ]];
    then
    ../tm --brief --profile -s 2 -a 2 -i 10001 -k 2 -t 4631 > profile4631r.txt &
    P1=$!
    ../tm --brief --profile -s 2 -a 3 -i 10001 -k 3 -t 32263324 &> profile32263324r.txt &
    P2=$!
    ../tm --brief --profile -s 3 -a 2 -i 10001 -k 2 -t 21457002  &> profile21457002r.txt &
    P3=$!
    ../tm --brief --profile -s 4 -a 2 -i 10001 -k 5 -t 74209803023 &> profile74209803023r.txt &
    P4=$!
    ../tm --brief --profile -s 5 -a 2 -i 10001 -k 4 -t 252090028326298  &> profile252090028326298r.txt &
    P5=$!
    ../tm --brief --profile -s 6 -a 2 -i 10001 -k 4 -t 4130363985567866121  &> profile4130363985567866121r.txt &
    P6=$!
    ../tm --brief --profile -s 7 -a 2 -i 10001 -k 9 -t 8223201221054750691960 &> profile8223201221054750691960r.txt &
    P7=$!
    ../tm --brief --profile -s 8 -a 2 -i 10001 -k 7 -t 196105202546554444571317643 &> profile196105202546554444571317643r.txt &
    P8=$!
    ../tm --brief --profile -s 9 -a 2 -i 10001 -k 2 -t 5247280021045053584652228990849 &> profile5247280021045053584652228990849r.txt &
    P9=$!
    ../tm --brief --profile -s 10 -a 2 -i 10001 -k 3 -t 197125200246148754014176544661820783 &> profile197125200246148754014176544661820783r.txt &
    P10=$!
    wait $P1 $P2 $P3 $P4 $P5 $P6 $P7 $P8 $P9 $P10

    tail -n +3 profile4631r.txt | awk '{ print $4;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > nc_profile4631r.txt;
    tail -n +3 profile4631r.txt | awk '{ print $2;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > amp_profile4631r.txt;
    paste amp_profile4631r.txt nc_profile4631r.txt > profile4631r.txt;

    tail -n +3 profile32263324r.txt | awk '{ print $4;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > nc_profile32263324r.txt;
    tail -n +3 profile32263324r.txt | awk '{ print $2;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > amp_profile32263324r.txt;
    paste amp_profile32263324r.txt nc_profile32263324r.txt > profile32263324r.txt;

    tail -n +3 profile21457002r.txt | awk '{ print $4;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > nc_profile21457002r.txt;
    tail -n +3 profile21457002r.txt | awk '{ print $2;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > amp_profile21457002r.txt;
    paste amp_profile21457002r.txt nc_profile21457002r.txt > profile21457002r.txt;

    tail -n +3 profile74209803023r.txt | awk '{ print $4;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > nc_profile74209803023r.txt;
    tail -n +3 profile74209803023r.txt | awk '{ print $2;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > amp_profile74209803023r.txt;
    paste amp_profile74209803023r.txt nc_profile74209803023r.txt > profile74209803023r.txt;

    tail -n +3 profile252090028326298r.txt | awk '{ print $4;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > nc_profile252090028326298r.txt;
    tail -n +3 profile252090028326298r.txt | awk '{ print $2;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > amp_profile252090028326298r.txt;
    paste amp_profile252090028326298r.txt nc_profile252090028326298r.txt > profile252090028326298r.txt;

    tail -n +3 profile4130363985567866121r.txt | awk '{ print $4;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > nc_profile4130363985567866121r.txt;
    tail -n +3 profile4130363985567866121r.txt | awk '{ print $2;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > amp_profile4130363985567866121r.txt;
    paste amp_profile4130363985567866121r.txt nc_profile4130363985567866121r.txt > profile4130363985567866121r.txt;

    tail -n +3 profile8223201221054750691960r.txt | awk '{ print $4;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 >  nc_profile8223201221054750691960r.txt;
    tail -n +3 profile8223201221054750691960r.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > amp_profile8223201221054750691960r.txt;
    paste amp_profile8223201221054750691960r.txt nc_profile8223201221054750691960r.txt > profile8223201221054750691960r.txt;

    tail -n +3 profile196105202546554444571317643r.txt | awk '{ print $4;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > nc_profile196105202546554444571317643r.txt;
    tail -n +3 profile196105202546554444571317643r.txt | awk '{ print $2;}'| ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > amp_profile196105202546554444571317643r.txt;
    paste amp_profile196105202546554444571317643r.txt nc_profile196105202546554444571317643r.txt > profile196105202546554444571317643r.txt;

    tail -n +3 profile5247280021045053584652228990849r.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > nc_profile5247280021045053584652228990849r.txt;
    tail -n +3 profile5247280021045053584652228990849r.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > amp_profile5247280021045053584652228990849r.txt;
    paste amp_profile5247280021045053584652228990849r.txt nc_profile5247280021045053584652228990849r.txt > profile5247280021045053584652228990849r.txt;

    tail -n +3 profile197125200246148754014176544661820783r.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > nc_profile197125200246148754014176544661820783r.txt;
    tail -n +3 profile197125200246148754014176544661820783r.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 40 -d 80 -1 > amp_profile197125200246148754014176544661820783r.txt;
    paste amp_profile197125200246148754014176544661820783r.txt nc_profile197125200246148754014176544661820783r.txt > profile197125200246148754014176544661820783r.txt;

    rm amp_profile4631r.txt nc_profile4631r.txt;
    rm amp_profile32263324r.txt nc_profile32263324r.txt;
    rm amp_profile21457002r.txt nc_profile21457002r.txt;
    rm amp_profile74209803023r.txt nc_profile74209803023r.txt;
    rm amp_profile252090028326298r.txt nc_profile252090028326298r.txt;
    rm amp_profile4130363985567866121r.txt nc_profile4130363985567866121r.txt;
    rm amp_profile8223201221054750691960r.txt nc_profile8223201221054750691960r.txt;
    rm amp_profile196105202546554444571317643r.txt nc_profile196105202546554444571317643r.txt;
    rm amp_profile5247280021045053584652228990849r.txt nc_profile5247280021045053584652228990849r.txt
    rm amp_profile197125200246148754014176544661820783r.txt nc_profile197125200246148754014176544661820783r.txt

gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "NormalProfilesArticler.pdf"
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
    set ylabel "Compression Profile"
    set datafile separator "\t"
    set style line 1 \
    linetype 1 linewidth 3 \
    pointtype 7 pointsize 0.01
    set style fill transparent solid 0.4 noborder
    plot "profile4631r.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#0060ad' title "Tape 4631, #Q=2, #{/Symbol S}=2", \
    "profile32263324r.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#7cf251' title "Tape 32263324, #Q=2, #{/Symbol S}=3", \
    "profile21457002r.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#ffbf00' title "Tape 21457002, #Q=3, #{/Symbol S}=2", \
    "profile74209803023r.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#ff7651' title "Tape 74209803023, #Q=4, #{/Symbol S}=2", \
    "profile252090028326298r.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#ff7700' title "Tape 252090028326298, #Q=5, #{/Symbol S}=2", \
    "profile4130363985567866121r.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#ff0000' title "Tape 4130363985567866121, #Q=6, #{/Symbol S}=2", \
    "profile8223201221054750691960r.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#347C17' title "Tape 8223201221054750691960, #Q=7, #{/Symbol S}=2", \
    "profile196105202546554444571317643r.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#98AFC7' title "Tape 196105202546554444571317643, #Q=8, #{/Symbol S}=2", \
    "profile5247280021045053584652228990849r.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#808080' title "Tape 5247280021045053584652228990849, #Q=9, #{/Symbol S}=2", \
    "profile197125200246148754014176544661820783r.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#2F4F4F' title "Tape 197125200246148754014176544661820783, #Q=10, #{/Symbol S}=2"
EOF

    rm profile4631r.txt profile21457002r.txt profile32263324r.txt  profile74209803023r.txt profile252090028326298r.txt;
    rm profile4130363985567866121r.txt profile8223201221054750691960r.txt profile196105202546554444571317643r.txt;
    rm profile5247280021045053584652228990849r.txt profile197125200246148754014176544661820783r.txt;
    mv NormalProfilesArticler.pdf ../profiles;

fi


# # ==============================================================================
# # Dynamical Profile of TM in provided file
# # ==============================================================================
if [[ "$DP" -eq "1" ]];
    then
    x=10001;

    ../tm --brief --dynprofile -s 2 -a 2 -i $x -k 2 -t 4631 > profile4631r.txt &
    P1=$!
    ../tm --brief --dynprofile -s 2 -a 3 -i $x -k 3 -t 32263324 > profile32263324r.txt &
    P2=$!
    ../tm --brief --dynprofile -s 3 -a 2 -i $x -k 2 -t 21457002 > profile21457002r.txt &
    P3=$!
    ../tm --brief --dynprofile -s 4 -a 2 -i $x -k 5 -t 74209803023 > profile74209803023r.txt &
    P4=$!
    wait $P1 $P2 $P3 $P4
    ../tm --brief --dynprofile -s 5 -a 2 -i $x -k 4 -t 252090028326298 > profile252090028326298r.txt &
    P5=$!
    ../tm --brief --dynprofile -s 6 -a 2 -i $x -k 5 -t 4130363985567866121 > profile4130363985567866121r.txt &
    P6=$!
    ../tm --brief --dynprofile -s 7 -a 2 -i $x -k 5 -t 8223201221054750691960 > profile8223201221054750691960r.txt &
    P7=$!
    ../tm --brief --dynprofile -s 8 -a 2 -i $x -k 7 -t 196105202546554444571317643 > profile196105202546554444571317643r.txt &
    P8=$!
    wait $P5 $P6 $P7 $P8
    ../tm --brief --dynprofile -s 9 -a 2 -i $x -k 2 -t 5247280021045053584652228990849 > profile5247280021045053584652228990849r.txt &
    P9=$!
    ../tm --brief --dynprofile -s 10 -a 2 -i $x -k 8 -t 197125200246148754014176544661820783 > profile197125200246148754014176544661820783r.txt &
    P10=$!
    wait $P9 $P10

    tail -n +3 profile4631r.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 2560 -1 > nc_profile4631r.txt;
    tail -n +3 profile4631r.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 2560 -1 > amp_profile4631r.txt;
    paste amp_profile4631r.txt nc_profile4631r.txt > profile4631.txt;

    tail -n +3 profile32263324r.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 2560 -1 > nc_profile32263324r.txt;
    tail -n +3 profile32263324r.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 2560 -1 > amp_profile32263324r.txt;
    paste amp_profile32263324r.txt nc_profile32263324r.txt > profile32263324.txt;

    tail -n +3 profile21457002r.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 5120 -1 > nc_profile21457002r.txt;
    tail -n +3 profile21457002r.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 5120 -1 > amp_profile21457002r.txt;
    paste amp_profile21457002r.txt nc_profile21457002r.txt > profile21457002.txt;

    tail -n +3 profile74209803023r.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 2560 -1 > nc_profile74209803023r.txt;
    tail -n +3 profile74209803023r.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 2560 -1 > amp_profile74209803023r.txt;
    paste amp_profile74209803023r.txt nc_profile74209803023r.txt > profile74209803023.txt;

    tail -n +3 profile252090028326298r.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 2560 -1 > nc_profile252090028326298r.txt;
    tail -n +3 profile252090028326298r.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 2560 -1 > amp_profile252090028326298r.txt;
    paste amp_profile252090028326298r.txt nc_profile252090028326298r.txt > profile252090028326298.txt;

    tail -n +3 profile4130363985567866121r.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 2560 -d 5120 -1 > nc_profile4130363985567866121r.txt;
    tail -n +3 profile4130363985567866121r.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 2560 -d 5120 -1 > amp_profile4130363985567866121r.txt;
    paste amp_profile4130363985567866121r.txt nc_profile4130363985567866121r.txt > profile4130363985567866121.txt;

    tail -n +3 profile8223201221054750691960r.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 2560 -d 5120 -1 > nc_profile8223201221054750691960r.txt;
    tail -n +3 profile8223201221054750691960r.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 2560 -d 5120 -1 > amp_profile8223201221054750691960r.txt;
    paste amp_profile8223201221054750691960r.txt nc_profile8223201221054750691960r.txt > profile8223201221054750691960.txt;

    tail -n +3 profile196105202546554444571317643r.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 5120 -1 > nc_profile196105202546554444571317643r.txt;
    tail -n +3 profile196105202546554444571317643r.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 5120 -1 > amp_profile196105202546554444571317643r.txt;
    paste amp_profile196105202546554444571317643r.txt nc_profile196105202546554444571317643r.txt > profile196105202546554444571317643.txt;

    tail -n +3 profile5247280021045053584652228990849r.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 5120 -1 > nc_profile5247280021045053584652228990849r.txt;
    tail -n +3 profile5247280021045053584652228990849r.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 5120 -1 > amp_profile5247280021045053584652228990849r.txt;
    paste amp_profile5247280021045053584652228990849r.txt nc_profile5247280021045053584652228990849r.txt > profile5247280021045053584652228990849.txt;

    tail -n +3 profile197125200246148754014176544661820783r.txt | awk '{ print $4;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 5120 -1 > nc_profile197125200246148754014176544661820783r.txt;
    tail -n +3 profile197125200246148754014176544661820783r.txt | awk '{ print $2;}' | ../goose/bin/goose-filter -p1 -w 1280 -d 5120 -1 > amp_profile197125200246148754014176544661820783r.txt;
    paste amp_profile197125200246148754014176544661820783r.txt nc_profile197125200246148754014176544661820783r.txt > profile197125200246148754014176544661820783.txt;

    rm amp_profile4631r.txt nc_profile4631r.txt;
    rm amp_profile32263324r.txt nc_profile32263324r.txt;
    rm amp_profile21457002r.txt nc_profile21457002r.txt;
    rm amp_profile74209803023r.txt nc_profile74209803023r.txt;
    rm amp_profile252090028326298r.txt nc_profile252090028326298r.txt;
    rm amp_profile4130363985567866121r.txt nc_profile4130363985567866121r.txt;
    rm amp_profile8223201221054750691960r.txt nc_profile8223201221054750691960r.txt;
    rm amp_profile196105202546554444571317643r.txt nc_profile196105202546554444571317643r.txt;
    rm amp_profile5247280021045053584652228990849r.txt nc_profile5247280021045053584652228990849r.txt;
    rm amp_profile197125200246148754014176544661820783r.txt nc_profile197125200246148754014176544661820783r.txt
 
gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set output "DynamicProfilesArticler.pdf"
    set boxwidth 0.5
    set size ratio 0.6
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:]
    set yrange [0:1.1]
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
    "profile4130363985567866121.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#ff0000' title "Tape 4130363985567866121, #Q=6, #{/Symbol S}=2", \
    "profile8223201221054750691960.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#347C17' title "Tape 8223201221054750691960, #Q=7, #{/Symbol S}=2", \
    "profile196105202546554444571317643.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#98AFC7' title "Tape 196105202546554444571317643, #Q=8, #{/Symbol S}=2", \
    "profile5247280021045053584652228990849.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#808080' title "Tape 5247280021045053584652228990849, #Q=9, #{/Symbol S}=2", \
    "profile197125200246148754014176544661820783.txt" using 1:2 with linespoints linestyle 1 linecolor rgb '#2F4F4F' title "Tape 197125200246148754014176544661820783, #Q=10, #{/Symbol S}=2"
EOF
    rm profile4631.txt profile21457002.txt profile32263324.txt  profile74209803023.txt profile252090028326298.txt;
    rm profile4130363985567866121.txt profile8223201221054750691960.txt profile196105202546554444571317643.txt;
    rm profile5247280021045053584652228990849.txt profile197125200246148754014176544661820783.txt;
    rm profile4631r.txt profile21457002r.txt profile32263324r.txt  profile74209803023r.txt profile252090028326298r.txt;
    rm profile4130363985567866121r.txt profile8223201221054750691960r.txt profile196105202546554444571317643r.txt;
    rm profile5247280021045053584652228990849r.txt profile197125200246148754014176544661820783r.txt;
    mv DynamicProfilesArticler.pdf ../profiles;
fi

# # ==============================================================================
# # string edition and  Profile in article
# # ==============================================================================

if [[ "$NC" -eq "1" ]];
    then
    cd .. ;
    ./tm --mutate | tail -n +2 > stringEdition.txt;
    mv stringEdition.txt ./scripts/stringEdition.txt;
    cd scripts;


gnuplot << EOF
    reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set size 0.98,1
    set output "StringNCwithEdition.pdf"
    set boxwidth 1
    set size ratio 0.6
    
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [100:0] 
    set yrange [0:1000]
    set zrange [0:1.1]
    set cbrange [0:1]

    set grid xtics lt -1
    set grid ytics lt -1
    set grid ztics lt -1
    set grid cbtics lt -1
    set border 3 front ls 101    
    
    set yzeroaxis lt 1 lw 2 lc rgb "black"
    set xzeroaxis lt 1 lw 2 lc rgb "black"

    set xyplane 0

    set xlabel "Percentage of substitutions" rotate parallel font "Verdana-Bold,12" offset 0,-1,0
    set ylabel "Fraction of block permutations" rotate parallel font "Verdana-Bold,12" offset 1
    set zlabel "Normalized Compression" rotate parallel font "Verdana-Bold,12" offset -2
    set cblabel 'NC Variation' font "Verdana-Bold,12"
    set xtics font "Verdana-Bold,10" offset 0,-1,0
    set ztics font "Verdana-Bold,10" offset -1
    set ytics font "Verdana-Bold,9" offset -1
    set cbtics font "Verdana-Bold,10" offset -1

    set datafile separator "\t"
    set title "Variation of NC with increase edition and Permutation of a String" font "Verdana-Bold,12"
    set palette defined (0 "#0048ff",30 "#00ffff",55 "#ffff00", 70 "#ffcc00",90 "#ff8000",100 "#ff0000",101 "#b50000")    
    splot "stringEdition.txt" with pm3d notitle
EOF
rm stringEdition.txt;
mv StringNCwithEdition.pdf ../resultPlots;

fi

# # ==============================================================================
# # parvovirus virus Profile in article
# # ==============================================================================

if [[ "$PVNC" -eq "1" ]];
    then
    cp ../resultText/Parvovirus_virus_nc.txt ./Parvovirus_virus_nc.txt

    # cd .. ;
    # ./tm --mutateVirus | tail -n +2 > virus_var2.txt;
    # mv virus_var2.txt ./scripts/virus_var2.txt;
    # cd scripts;

gnuplot << EOF
reset
    set terminal pdfcairo enhanced color font 'Verdana,8'
    set size 0.98,1
    set output "Parvovirus.pdf"
    set boxwidth 1
    set size ratio 0.6
    
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:100] 
    set yrange [0:6000]
    set zrange [0:1.1]
    set cbrange [0:1]

    set grid xtics lt -1 
    set grid ytics lt -1
    set grid ztics lt -1
    set grid cbtics lt -1
    set border 3 front ls 101    
    
    set yzeroaxis lt 1 lw 2 lc rgb "black"
    set xzeroaxis lt 1 lw 2 lc rgb "black"

    set xyplane 0
    
    set xlabel "Percentage of substitutions" rotate parallel font "Verdana-Bold,12" offset 0,-1,0
    set ylabel "Fraction of block permutations" rotate parallel font "Verdana-Bold,12" offset 1
    set zlabel "Normalized Compression" rotate parallel font "Verdana-Bold,12" offset -2
    set cblabel 'NC Variation' font "Verdana-Bold,12"
    set xtics font "Verdana-Bold,10" offset 0,-1,0
    set ztics font "Verdana-Bold,10" offset -1
    set ytics font "Verdana-Bold,9" offset -1
    set cbtics font "Verdana-Bold,10" offset -1
    set datafile separator "\t"
    set palette defined (0 "#0048ff",30 "#00ffff",55 "#ffff00", 70 "#ffcc00",90 "#ff8000",100 "#ff0000",101 "#b50000") 
    set title "MH201455.1 Human parvovirus B19 isolate BX1, complete genome \n NC variation with Edition and Permutations" font "Verdana-Bold,12"
    splot "Parvovirus_virus_nc.txt"  with pm3d notitle

EOF

mv Parvovirus.pdf ../resultPlots;
rm Parvovirus_virus_nc.txt;
fi

# # ==============================================================================
# # Herpes virus Profile in article
# # ==============================================================================

if [[ "$HVNC" -eq "1" ]];
    then
    cp ../resultText/Herpes_simplex_virus_nc.txt ./Herpes_simplex_virus_nc.txt

gnuplot << EOF
reset
    set terminal pdfcairo enhanced color font 'Verdana,8';
    set size 0.98,1
    set output "Herpes.pdf"
    set boxwidth 2
    set size ratio 0.6
    
    set style line 101 lc rgb '#000000' lt 1 lw 3
    set key outside horiz center top
    set tics nomirror out scale 0.75
    set xrange [0:100] 
    set yrange [0:160000]
    set zrange [0:1.1]
    set cbrange [0:1]
    set rmargin 10
    set grid xtics lt -1 
    set grid ytics lt -1
    set grid ztics lt -1
    set grid cbtics lt -1
    set border 3 front ls 101    
    
    set yzeroaxis lt 1 lw 2 lc rgb "black"
    set xzeroaxis lt 1 lw 2 lc rgb "black"

    set xyplane 0
    
    set xlabel "Percentage of substitutions" rotate parallel font "Verdana-Bold,12" offset 0,-1,0
    set ylabel "Fraction of block permutations" rotate parallel font "Verdana-Bold,12" offset 1
    set zlabel "Normalized Compression" rotate parallel font "Verdana-Bold,12" offset -2
    set cblabel 'NC Variation' font "Verdana-Bold,12"
    set xtics font "Verdana-Bold,10" offset 0,-1,0
    set ztics font "Verdana-Bold,10" offset -1
    set ytics font "Verdana-Bold,9" offset -1
    set cbtics font "Verdana-Bold,10" offset -1

    set datafile separator "\t"
    set palette defined (0 "#0048ff",30 "#00ffff",55 "#ffff00", 70 "#ffcc00",90 "#ff8000",100 "#ff0000",101 "#b50000") 
    set title "Z86099.2 Herpes simplex virus type 2 (strain HG52), complete genome \n NC variation with Edition and Permutations" font "Verdana-Bold,12"
    splot "Herpes_simplex_virus_nc.txt"  with pm3d notitle

EOF

mv Herpes.pdf ../resultPlots;
rm Herpes_simplex_virus_nc.txt;

fi