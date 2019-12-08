#!/bin/bash
#

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
< ../resultText/2sts2alp.txt awk -v b="$INITst2" -v e="$ENDst2" ' {if ( $1 >= b && $1 <= e ) print $1}'> Region2sts2alph.txt;
a=$(wc -l Region2sts2alph.txt | awk '{print $1}');
shuf -n $a ../resultText/2sts2alp.txt | awk -v a="$INIT2st2" -v b="$INITst2" -v e="$ENDst2" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1}' > Region_Outside_2sts2alph.txt;
echo "$(shuf -n 1000 Region_Outside_2sts2alph.txt)" > Region_Outside_2sts2alph.txt
echo "$(shuf -n 1000 Region2sts2alph.txt)" > Region2sts2alph.txt;

#=============================================================================
< ../resultText/2sts3alp.txt awk -v b="$INITst2alp3" -v e="$ENDst2alp3" ' {if ( $1 >= b && $1 <= e ) print $1}' > Region2sts3alph.txt;
a=$(wc -l Region2sts3alph.txt | awk '{print $1}');
shuf -n $a ../resultText/2sts3alp.txt | awk -v a="$INIT2st2alp3" -v b="$INITst2alp3" -v e="$ENDst2alp3" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1}' > Region_Outside_2sts3alph.txt;
echo "$(shuf -n 1000 Region_Outside_2sts3alph.txt)" > Region_Outside_2sts3alph.txt
echo "$(shuf -n 1000 Region2sts3alph.txt)" > Region2sts3alph.txt;
#=============================================================================
< ../resultText/3sts2alp.txt  awk -v b="$INITst3" -v e="$ENDst3" ' {if ( $1 >= b && $1 <= e ) print $1 }' > Region3sts2alph.txt;
a=$(wc -l Region3sts2alph.txt | awk '{print $1}');
shuf -n $a ../resultText/3sts2alp.txt | awk -v a="$INIT2st3" -v b="$INITst3" -v e="$ENDst3" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1 }' > Region_Outside_3sts2alph.txt;
echo "$(shuf -n 1000 Region_Outside_3sts2alph.txt)" > Region_Outside_3sts2alph.txt
echo "$(shuf -n 1000 Region3sts2alph.txt)" > Region3sts2alph.txt;
#=============================================================================
< ../resultText/4sts2alp.txt awk -v b="$INITst4" -v e="$ENDst4" ' {if ( $1 >= b && $1 <= e ) print $1 }' > Region4sts2alph.txt;
a=$(wc -l Region4sts2alph.txt | awk '{print $1}');
shuf -n $a ../resultText/4sts2alp.txt | awk -v a="$INIT2st4" -v b="$INITst4" -v e="$ENDst4" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1 }' > Region_Outside_4sts2alph.txt;
echo "$(shuf -n 1000 Region_Outside_4sts2alph.txt)" > Region_Outside_4sts2alph.txt
echo "$(shuf -n 1000 Region4sts2alph.txt)" > Region4sts2alph.txt;
#=============================================================================
< ../resultText/5sts2alp.txt awk -v b="$INITst5" -v e="$ENDst5" ' {if ( $1 >= b && $1 <= e ) print $1 }' > Region5sts2alph.txt;
a=$(wc -l Region5sts2alph.txt | awk '{print $1}');
shuf -n $a ../resultText/5sts2alp.txt | awk -v a="$INIT2st5" -v b="$INITst5" -v e="$ENDst5" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1 }' > Region_Outside_5sts2alph.txt;
echo "$(shuf -n 1000 Region_Outside_5sts2alph.txt)" > Region_Outside_5sts2alph.txt
echo "$(shuf -n 1000 Region5sts2alph.txt)" > Region5sts2alph.txt;
#=============================================================================
< ../resultText/6sts2alp.txt  awk -v b="$INITst6" -v e="$ENDst6" ' {if ( $1 >= b && $1 <= e ) print $1 }' > Region6sts2alph.txt;
a=$(wc -l Region6sts2alph.txt | awk '{print $1}');
shuf -n $a ../resultText/6sts2alp.txt | awk -v a="$INIT2st6" -v b="$INITst6" -v e="$ENDst6" ' {if ( ($1 > a && $1 < b) || $1 > e ) print $1 }'> Region_Outside_6sts2alph.txt;
echo "$(shuf -n 1000 Region_Outside_6sts2alph.txt)" > Region_Outside_6sts2alph.txt
echo "$(shuf -n 1000 Region6sts2alph.txt)" > Region6sts2alph.txt;
#=============================================================================
#=============================================================================
# Get Metrics
#=============================================================================
function getRuleNC {
    while read p; do
        ../tm --brief --ruleMetrics -s $2 -a $3 -i 10 -t $p 
    done < $1;
}

getRuleNC "Region2sts2alph.txt" 2 2 > Region2sts2alph_rule_metrics.txt;
P1=$!
getRuleNC "Region_Outside_2sts2alph.txt" 2 2 > Region_Outside_2sts2alph_rule_metrics.txt &
P2=$!
wait $P1 $P2

getRuleNC "Region2sts3alph.txt" 2 3 > Region2sts3alph_rule_metrics.txt &
P3=$!
getRuleNC "Region_Outside_2sts3alph.txt" 2 2 > Region_Outside_2sts3alph_rule_metrics.txt &
P4=$!
wait $P3 $P4

getRuleNC "Region3sts2alph.txt" 3 2 > Region3sts2alph_rule_metrics.txt &
P5=$!
getRuleNC "Region_Outside_3sts2alph.txt" 2 2 > Region_Outside_3sts2alph_rule_metrics.txt &
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
getRuleNC "Region_Outside_6sts2alph.txt" 5 2 > Region_Outside_6sts2alph_rule_metrics.txt &
P12=$!
wait $P11 $P12


