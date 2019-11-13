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
# cat ../resultText/2sts2alp.txt | awk -v b="$INITst2" -v e="$ENDst2" ' {if ( $1 >= b && $1 <= e ) print $1}'> Region2sts2alph.txt;
# cat ../resultText/2sts3alp.txt | awk -v b="$INITst2alp3" -v e="$ENDst2alp3" ' {if ( $1 >= b && $1 <= e ) print $1}' > Region2sts3alph.txt;
# cat ../resultText/3sts2alp.txt | awk -v b="$INITst3" -v e="$ENDst3" ' {if ( $1 >= b && $1 <= e ) print $1}' > Region3sts2alph.txt;
# cat ../resultText/4sts2alp.txt | awk -v b="$INITst4" -v e="$ENDst4" ' {if ( $1 >= b && $1 <= e ) print $1}' > Region4sts2alph.txt;
# cat ../resultText/5sts2alp.txt | awk -v b="$INITst5" -v e="$ENDst5" ' {if ( $1 >= b && $1 <= e ) print $1}' > Region5sts2alph.txt;
# cat ../resultText/6sts2alp.txt | awk -v b="$INITst6" -v e="$ENDst6" ' {if ( $1 >= b && $1 <= e ) print $1}' > Region6sts2alph.txt;

function getStateMatrix {
    while read p; do
        ../tm --brief --StMatrix -s $2 -a $3 -t $p 
    done < $1;

}
getStateMatrix "Region2sts2alph.txt" 2 2 > Region2sts2alph_state_matrix.txt;
getStateMatrix "Region2sts3alph.txt" 2 3 > Region2sts3alph_state_matrix.txt;
getStateMatrix "Region3sts2alph.txt" 3 2 > Region3sts2alph_state_matrix.txt;
getStateMatrix "Region4sts2alph.txt" 4 2 > Region4sts2alph_state_matrix.txt;
getStateMatrix "Region5sts2alph.txt" 5 2 > Region5sts2alph_state_matrix.txt;
getStateMatrix "Region6sts2alph.txt" 6 2 > Region6sts2alph_state_matrix.txt;

