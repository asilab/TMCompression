#!/bin/bash
#
if [ $# -eq 0 ]; then
    echo "No arguments provided"
    exit 1
fi

# ==============================================================================
# Variables
# ==============================================================================
state=$1;
txtName=$1"st.txt";
savePath=$1"st"

# tail -n +4 $txtName | head -n -3 | sort -k 6,6 |awk '$4 < 100 { next } { print }' | tail -n 50 

tail -n +4 $txtName | head -n -3 | sort -k 6,6 |awk '$4 < 100 { next } { print }' | tail -n 50 | awk ' { print $1}' > InterestingMachines.txt;

while read p; do
   bash ./Profile.sh $p $savePath
done <InterestingMachines.txt
