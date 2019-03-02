#!/bin/bash
#
if [ $# -ne 3 ]; then
    echo "No arguments provided";
    exit 1;
fi

# ==============================================================================
# Variables
# ==============================================================================

# O que fazer aqui:
# 1 Filtra so os resultados de um dado ficheiro
# 2 Pede o ficheiro e faz o prefil com os membros do ficheiro
# 3 Pede o ficheiro e faz o prefil dynamico com os membros do ficheiro

FILTER=$1;
PROFILE=$2;
DYNAMICPROFILE=$3;

NUMBERITERATION=100;
K=2;
# ==============================================================================
# FILTER MOST RELAVANT MACHINES
# ==============================================================================

if [[ "$FILTER" -eq "1" ]];
    then
    echo "Please insert a specific file to be filtered ex: 2st.txt"
    read FILENAME;
    
    if [[ $FILENAME == *.txt ]]
      then
        if [ -f $FILENAME ]; then

            tail -n +4 $FILENAME | head -n -3 | sort -k 6,6 |awk '$4 < 100 { next } { print }' | tail -n 50 | awk ' { print $1}' > "InterestingTM"$FILENAME;

        else
            echo "File $FILENAME does not exist.";
        fi
    else
        echo "Please select .txt file";
    fi
fi

if [[ "$PROFILE" -eq "1" ]];
then
    echo "Please insert filtered file with machines that will make the profile: Ex: InterestingTM2st.txt"
    read FILENAME;
    if [[ $FILENAME == *.txt ]]
      then
        if [ -f $FILENAME ]; then
            echo "Please insert #States: Ex: 2"
            read STATES;
            echo "Please insert #Alphabet: Ex: 2"
            read ALPHABET;

            while read p; do
                bash ./Profile.sh $p $STATES $ALPHABET $NUMBERITERATION $K
            done <$FILENAME
        fi
    fi
fi

if [[ "$DYNAMICPROFILE" -eq "1" ]];
then
    echo "Please insert filtered file with machines that will make the dynamic profile: Ex: InterestingTM2st.txt"
    read FILENAME;
    if [[ $FILENAME == *.txt ]]
      then
        if [ -f $FILENAME ]; then
            echo "Please insert #States: Ex: 2"
            read STATES;
            echo "Please insert #Alphabet: Ex: 2"
            read ALPHABET;

            while read p; do 
                bash ./DynamicProfile.sh $p $STATES $ALPHABET $NUMBERITERATION $K
            done <$FILENAME
        fi
    fi
fi
