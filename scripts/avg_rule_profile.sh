#!/bin/bash
#
if [ $# -ne 2 ]; then
    echo "Not enough arguments arguments provided, you need to provide 3 arguments:";
    echo "All args are boolean (0 or 1)";
    echo "";
    echo "If 1st Argument == 1: Create File with average profiles for a state and alphabet";
    echo "bash avg_rule_profile.sh 1 0";
    echo "If 2nd Argument == 1: Plots average of File";
    echo "bash avg_rule_profile.sh 0 1";
    echo "";
    exit 1;
fi


# ==============================================================================
# Variables
# ==============================================================================
FILE=$1;
PLOT=$2;
# Default Values
NUMBERITERATION=1001;
K=2;
SavePathText="../resultText";
SavePathPlot="../resultPlots";

# ==============================================================================
# Average of Profiles
# ==============================================================================

function getprofile {
    while read line; do
        #get k
        #get Machine
        TM=$(echo $line | awk '{ print $1;}');
        K=2;
        ../tm --brief --ruleProfile -s $2 -a $3 -i $4 -k $K -t $TM | tail -n +3
    done < $1;
}

function averageProfile {
    FILENAME=$1;
    STATE=$2;
    ALPHABET=$3;
    NUMBERITERATION=1001;
    REGION=$4;
    if [[ $FILENAME == *.txt ]];
        then
        if [ -f $FILENAME ];then
            sort -n -k1 $FILENAME > TMP;
            getprofile "TMP" "$STATE" "$ALPHABET" "$NUMBERITERATION" > TMP2;
            ../ioGrowthAverage TMP2 > AVGRuleProfile${REGION}Region${STATE}St${ALPHABET}AlphTM.txt
            rm TMP TMP2;
        else
            echo "File $FILENAME does not exist.";
        fi
    else
        echo "Please select .txt file";
    fi
}

if [[ "$FILE" -eq "1" ]];
    then
    cd ${SavePathText};
    bash ../scripts/getRegionRuleValues.sh 1 0 0 0;
    averageProfile Region2sts2alph.txt 2 2 "in";
    averageProfile Region2sts3alph.txt 2 3 "in";
    averageProfile Region3sts2alph.txt 3 2 "in";
    averageProfile Region4sts2alph.txt 4 2 "in";
    averageProfile Region5sts2alph.txt 5 2 "in";
    averageProfile Region6sts2alph.txt 6 2 "in";

    averageProfile Region_Outside_2sts2alph.txt 2 2 "out";
    averageProfile Region_Outside_2sts3alph.txt 2 3 "out";
    averageProfile Region_Outside_3sts2alph.txt 3 2 "out";
    averageProfile Region_Outside_4sts2alph.txt 4 2 "out";
    averageProfile Region_Outside_5sts2alph.txt 5 2 "out";
    averageProfile Region_Outside_6sts2alph.txt 6 2 "out";
    cd ../scripts;
fi

# ==============================================================================
#  Plot Profiles
# ==============================================================================

function plot {
        < $1 awk '{ print $1,"\t",$4}' > NC_rule_in;
        < $2 awk '{ print $1,"\t",$4}' > NC_rule_out;

        gnuplot << EOF
        reset
        set terminal pdfcairo enhanced color font 'Verdana,8'
        set output "${5}"
        set style line 1 lt rgb "red" lw 3
        set xrange [0:990]
        set yrange [0:1]
        set key left top
        set grid ytics lt -1
        set style fill solid
        set xlabel "Number Iterations"
        set ylabel "Rule Complexity Profile"
        set datafile separator "\t"
        set xtics
        set style fill transparent solid 0.5 noborder
        set style line 1 \
        linetype 1 linewidth 3 \
        pointtype 7 pointsize 0.01
        plot "NC_rule_in" using 1:2 with linespoints linestyle 1 linecolor rgb '#41A317' title "Average Rule Profile inside Region for #Q=${3}, #{/Symbol S}=${4}" ,\
        "NC_rule_out" using 1:2 with linespoints linestyle 1 linecolor rgb '#E41B17' title "Average Rule Profile ouside Region #Q=${3}, #{/Symbol S}=${4}"
EOF
    mv $5 ${SavePathPlot}
    rm NC_rule_in NC_rule_out;
}



if [[ "$PLOT" -eq "1" ]];
    then
    cd ${SavePathText};

    plot AVGRuleProfileinRegion2St2AlphTM.txt AVGRuleProfileoutRegion2St2AlphTM.txt 2 2 AVGRuleProfile2St2Alph.pdf;
    plot AVGRuleProfileinRegion2St3AlphTM.txt AVGRuleProfileoutRegion2St3AlphTM.txt 2 3 AVGRuleProfile2St3Alph.pdf;
    plot AVGRuleProfileinRegion3St2AlphTM.txt AVGRuleProfileoutRegion3St2AlphTM.txt 3 2 AVGRuleProfile3St2Alph.pdf;
    plot AVGRuleProfileinRegion4St2AlphTM.txt AVGRuleProfileoutRegion4St2AlphTM.txt 4 2 AVGRuleProfile4St2Alph.pdf;
    plot AVGRuleProfileinRegion5St2AlphTM.txt AVGRuleProfileoutRegion5St2AlphTM.txt 5 2 AVGRuleProfile5St2Alph.pdf;
    plot AVGRuleProfileinRegion6St2AlphTM.txt AVGRuleProfileoutRegion6St2AlphTM.txt 6 2 AVGRuleProfile6St2Alph.pdf;
    
    rm AVGRuleProfileinRegion2St2AlphTM.txt AVGRuleProfileoutRegion2St2AlphTM.txt;
    rm AVGRuleProfileinRegion2St3AlphTM.txt AVGRuleProfileoutRegion2St3AlphTM.txt;
    rm AVGRuleProfileinRegion3St2AlphTM.txt AVGRuleProfileoutRegion3St2AlphTM.txt;
    rm AVGRuleProfileinRegion4St2AlphTM.txt AVGRuleProfileoutRegion4St2AlphTM.txt;
    rm AVGRuleProfileinRegion5St2AlphTM.txt AVGRuleProfileoutRegion5St2AlphTM.txt;
    rm AVGRuleProfileinRegion6St2AlphTM.txt AVGRuleProfileoutRegion6St2AlphTM.txt;
    rm Region*.txt
    cd ../scripts;
fi