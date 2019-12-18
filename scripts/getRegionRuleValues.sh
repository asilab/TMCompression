#!/bin/bash
#
if [ $# -ne 4 ]; then
    echo "Not enough arguments arguments provided, you need to provide 3 arguments:";
    echo "All args are boolean (0 or 1)";
    echo "";
    echo "If 1st Argument == 1: Get Regions";
    echo "bash getRegionValues.sh 1 0 0 0";
    echo "If 2nd Argument == 1: Get Rule Vector of TMS";
    echo "bash getRegionValues.sh 0 1 0 0";
    echo "If 3rd Argument == 1: Compute NC of Rule vectors";
    echo "bash getRegionValues.sh 0 0 1 0";
    echo "If 4th Argument == 1: Average NC of rule vectors obtained and Plot average NC of rule vectors obtained";
    echo "bash getRegionValues.sh 0 0 0 1";
    echo "";
    exit 1;
fi

#==============================================================================
# Global  Variables
#==============================================================================
REGION=$1;
GETTAPE=$2;
GETRULENC=$3;
AVERAGERESULTS=$4;

#==============================================================================
#   Obtain Regions
#==============================================================================
if [[ "$REGION" -eq "1" ]];
    then

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
    cd ../resultText;
    < 2sts2alp.txt awk -v b="$INITst2" -v e="$ENDst2" ' {if ( $1 >= b && $1 <= e ) print $1}'> Region2sts2alph.txt;
    a=$(wc -l Region2sts2alph.txt | awk '{print $1}');
    shuf -n $a 2sts2alp.txt | awk -v a="$INIT2st2" -v b="$INITst2" -v e="$ENDst2" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1}' > Region_Outside_2sts2alph.txt;
    echo "$(shuf -n 3000 Region_Outside_2sts2alph.txt)" > Region_Outside_2sts2alph.txt
    echo "$(shuf -n 3000 Region2sts2alph.txt)" > Region2sts2alph.txt;

    #=============================================================================
    < 2sts3alp.txt awk -v b="$INITst2alp3" -v e="$ENDst2alp3" ' {if ( $1 >= b && $1 <= e ) print $1}' > Region2sts3alph.txt;
    a=$(wc -l Region2sts3alph.txt | awk '{print $1}');
    shuf -n $a ../resultText/2sts3alp.txt | awk -v a="$INIT2st2alp3" -v b="$INITst2alp3" -v e="$ENDst2alp3" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1}' > Region_Outside_2sts3alph.txt;
    echo "$(shuf -n 5000 Region_Outside_2sts3alph.txt)" > Region_Outside_2sts3alph.txt
    echo "$(shuf -n 5000 Region2sts3alph.txt)" > Region2sts3alph.txt;
    #=============================================================================
    < 3sts2alp.txt  awk -v b="$INITst3" -v e="$ENDst3" ' {if ( $1 >= b && $1 <= e ) print $1 }' > Region3sts2alph.txt;
    a=$(wc -l Region3sts2alph.txt | awk '{print $1}');
    shuf -n $a 3sts2alp.txt | awk -v a="$INIT2st3" -v b="$INITst3" -v e="$ENDst3" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1 }' > Region_Outside_3sts2alph.txt;
    echo "$(shuf -n 5000 Region_Outside_3sts2alph.txt)" > Region_Outside_3sts2alph.txt
    echo "$(shuf -n 5000 Region3sts2alph.txt)" > Region3sts2alph.txt;
    #=============================================================================
    < 4sts2alp.txt awk -v b="$INITst4" -v e="$ENDst4" ' {if ( $1 >= b && $1 <= e ) print $1 }' > Region4sts2alph.txt;
    a=$(wc -l Region4sts2alph.txt | awk '{print $1}');
    shuf -n $a 4sts2alp.txt | awk -v a="$INIT2st4" -v b="$INITst4" -v e="$ENDst4" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1 }' > Region_Outside_4sts2alph.txt;
    echo "$(shuf -n 5000 Region_Outside_4sts2alph.txt)" > Region_Outside_4sts2alph.txt
    echo "$(shuf -n 5000 Region4sts2alph.txt)" > Region4sts2alph.txt;
    #=============================================================================
    < 5sts2alp.txt awk -v b="$INITst5" -v e="$ENDst5" ' {if ( $1 >= b && $1 <= e ) print $1 }' > Region5sts2alph.txt;
    a=$(wc -l Region5sts2alph.txt | awk '{print $1}');
    shuf -n $a 5sts2alp.txt | awk -v a="$INIT2st5" -v b="$INITst5" -v e="$ENDst5" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1 }' > Region_Outside_5sts2alph.txt;
    echo "$(shuf -n 5000 Region_Outside_5sts2alph.txt)" > Region_Outside_5sts2alph.txt
    echo "$(shuf -n 5000 Region5sts2alph.txt)" > Region5sts2alph.txt;
    #=============================================================================
    < 6sts2alp.txt  awk -v b="$INITst6" -v e="$ENDst6" ' {if ( $1 >= b && $1 <= e ) print $1 }' > Region6sts2alph.txt;
    a=$(wc -l Region6sts2alph.txt | awk '{print $1}');
    shuf -n $a 6sts2alp.txt | awk -v a="$INIT2st6" -v b="$INITst6" -v e="$ENDst6" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1 }'> Region_Outside_6sts2alph.txt;
    echo "$(shuf -n 5000 Region_Outside_6sts2alph.txt)" > Region_Outside_6sts2alph.txt
    echo "$(shuf -n 5000 Region6sts2alph.txt)" > Region6sts2alph.txt;
    #=============================================================================
    cd ../scripts;
fi

#=============================================================================
# Get Rules vector
#=============================================================================

if [[ "$GETTAPE" -eq "1" ]];
    then
    cd ../resultText;

    function getRuleTape {
        while read p; do
            ../tm --brief --ruleTape -s $2 -a $3 -i 100 -t $p
        done < $1;
    }

    getRuleTape "Region2sts2alph.txt" 2 2 > Region2sts2alph_rule_tape.txt &
    P1=$!
    getRuleTape "Region_Outside_2sts2alph.txt" 2 2 > Region_Outside_2sts2alph_rule_tape.txt &
    P2=$!
    wait $P1 $P2

    getRuleTape "Region2sts3alph.txt" 2 3 > Region2sts3alph_rule_tape.txt &
    P3=$!
    getRuleTape "Region_Outside_2sts3alph.txt" 2 3 > Region_Outside_2sts3alph_rule_tape.txt &
    P4=$!
    wait $P3 $P4

    getRuleTape "Region3sts2alph.txt" 3 2 > Region3sts2alph_rule_tape.txt &
    P5=$!
    getRuleTape "Region_Outside_3sts2alph.txt" 3 2 > Region_Outside_3sts2alph_rule_tape.txt &
    P6=$!
    wait $P5 $P6

    getRuleTape "Region4sts2alph.txt" 4 2 > Region4sts2alph_rule_tape.txt &
    P7=$!
    getRuleTape "Region_Outside_4sts2alph.txt" 4 2 >Region_Outside_4sts2alph_rule_tape.txt &
    P8=$!
    wait $P7 $P8

    getRuleTape "Region5sts2alph.txt" 5 2 > Region5sts2alph_rule_tape.txt &
    P9=$!
    getRuleTape "Region_Outside_5sts2alph.txt" 5 2 > Region_Outside_5sts2alph_rule_tape.txt &
    P10=$!
    wait $P9 $P10

    getRuleTape "Region6sts2alph.txt" 6 2 > Region6sts2alph_rule_tape.txt &
    P11=$!
    getRuleTape "Region_Outside_6sts2alph.txt" 6 2 > Region_Outside_6sts2alph_rule_tape.txt &
    P12=$!
    wait $P11 $P12
    cd ../scripts;
fi
#=============================================================================
# Get Metrics
#=============================================================================
if [[ "$GETRULENC" -eq "1" ]];
    then
    cd ../resultText;
    
    function getRuleNC {
        while read p; do
            ../tm --brief --ruleMetrics -s $2 -a $3 -i 1000 -t $p    
        done < $1;
    }

    getRuleNC "Region2sts2alph.txt" 2 2 > Region2sts2alph_rule_metrics.txt &
    P1=$!
    getRuleNC "Region_Outside_2sts2alph.txt" 2 2 > Region_Outside_2sts2alph_rule_metrics.txt &
    P2=$!
    wait $P1 $P2

    getRuleNC "Region2sts3alph.txt" 2 3 > Region2sts3alph_rule_metrics.txt &
    P3=$!
    getRuleNC "Region_Outside_2sts3alph.txt" 2 3 > Region_Outside_2sts3alph_rule_metrics.txt &
    P4=$!
    wait $P3 $P4

    getRuleNC "Region3sts2alph.txt" 3 2 > Region3sts2alph_rule_metrics.txt &
    P5=$!
    getRuleNC "Region_Outside_3sts2alph.txt" 3 2 > Region_Outside_3sts2alph_rule_metrics.txt &
    P6=$!
    wait $P5 $P6

    getRuleNC "Region4sts2alph.txt" 4 2 > Region4sts2alph_rule_metrics.txt &
    P7=$!
    getRuleNC "Region_Outside_4sts2alph.txt" 4 2 >Region_Outside_4sts2alph_rule_metrics.txt &
    P8=$!
    wait $P7 $P8

    getRuleNC "Region5sts2alph.txt" 5 2 > Region5sts2alph_rule_metrics.txt &
    P9=$!
    getRuleNC "Region_Outside_5sts2alph.txt" 5 2 > Region_Outside_5sts2alph_rule_metrics.txt &
    P10=$!
    wait $P9 $P10

    getRuleNC "Region6sts2alph.txt" 6 2 > Region6sts2alph_rule_metrics.txt &
    P11=$!
    getRuleNC "Region_Outside_6sts2alph.txt" 6 2 > Region_Outside_6sts2alph_rule_metrics.txt &
    P12=$!
    wait $P11 $P12
    cd ../scripts;
fi

#=============================================================================
# Average Rule Metrics
#=============================================================================
if [[ "$AVERAGERESULTS" -eq "1" ]];
    then
    cd ../resultText;

    ../ioAverage2 Region2sts2alph_rule_metrics.txt >> AVG_Region_rule_metrics
    ../ioAverage2 Region_Outside_2sts2alph_rule_metrics.txt >> AVG_Region_Outside_rule_metrics
    
    ../ioAverage2 Region2sts3alph_rule_metrics.txt >> AVG_Region_rule_metrics
    ../ioAverage2 Region_Outside_2sts3alph_rule_metrics.txt >> AVG_Region_Outside_rule_metrics

    ../ioAverage2 Region3sts2alph_rule_metrics.txt >> AVG_Region_rule_metrics
    ../ioAverage2 Region_Outside_3sts2alph_rule_metrics.txt >> AVG_Region_Outside_rule_metrics

    ../ioAverage2 Region4sts2alph_rule_metrics.txt >> AVG_Region_rule_metrics
    ../ioAverage2 Region_Outside_4sts2alph_rule_metrics.txt >> AVG_Region_Outside_rule_metrics

    ../ioAverage2 Region5sts2alph_rule_metrics.txt >> AVG_Region_rule_metrics
    ../ioAverage2 Region_Outside_5sts2alph_rule_metrics.txt >> AVG_Region_Outside_rule_metrics

    ../ioAverage2 Region6sts2alph_rule_metrics.txt >> AVG_Region_rule_metrics
    ../ioAverage2 Region_Outside_6sts2alph_rule_metrics.txt >> AVG_Region_Outside_rule_metrics


    printf "1\n3\n5\n7\n9\n11" > Index1;
    printf "2\n4\n6\n8\n10\n12"> Index2;

    echo "$(paste Index1 AVG_Region_rule_metrics)" > AVG_Region_rule_metrics
    echo "$(paste Index2 AVG_Region_Outside_rule_metrics)" > AVG_Region_Outside_rule_metrics

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
        plot "AVG_Region_rule_metrics" using 1:3 with boxes linecolor '#41A317' title "Inside Region",\
        "AVG_Region_Outside_rule_metrics" using 1:3 with boxes linecolor '#E41B17' title "Outside Region"
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
        set yrange [0:0.05]
        set border 3 front ls 101
        set grid ytics lt -1
        set style fill solid
        set format '%g'
        set xtics font ", 6"
        set xlabel "Inside, Outside"
        set ylabel "Normalized Compression"
        set datafile separator "\t"
        plot "AVG_Region_rule_metrics" using 1:4 with boxes linecolor '#41A317' title "Inside Region",\
        "AVG_Region_Outside_rule_metrics" using 1:4 with boxes linecolor '#E41B17' title "Outside Region"
EOF

    pdfunite SC.pdf NC.pdf AverageInsidevsOUtsideRule.pdf;
    mv AverageInsidevsOUtsideRule.pdf ../resultPlots/
    rm NC* SC* 
    rm Index1 Index2;
    rm AVG_Region_rule_metrics AVG_Region_Outside_rule_metrics;
    rm Region*_rule_metrics.txt;
    rm Region*_rule_tape.txt;
    rm Region*alph.txt;
    cd ../scripts;
    
fi