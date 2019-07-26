#!/bin/bash
#
if [ $# -ne 3 ]; then
    echo "Not enough arguments arguments provided, you need to provide 3 arguments:";
    echo "All args are boolean (0 or 1)";
    echo "";
    echo "If 1st Argument == 1: Filters are the results of a given file and provide the 50 most statistically complex machines";
    echo "bash filteringResults.sh 1 0 0";
    echo "";
    echo "If 2nd Argument == 1:Requests the file and make the profile with the turing machines present in the file in the form of its indexes";
    echo "bash filteringResults.sh 0 1 0";
    echo "";
    echo "If 3rd Argument == 1:Requests the file and make the dynamical profile with the turing machines present in the file in the form of its indexes";
    echo "bash filteringResults.sh 0 0 1";
    echo "";
    exit 1;
fi

# ==============================================================================
# Variables
# ==============================================================================
FILTER=$1;
PROFILE=$2;
DYNAMICPROFILE=$3;

# Default Values
NUMBERITERATION=50000;
K=2;
SavePath="../profiles/";

# ==============================================================================
# FILTER MOST RELEVANT MACHINES
# ==============================================================================

if [[ "$FILTER" -eq "1" ]];
    then
    cd ../resultText;
    echo "Please insert a specific file to be filtered ex: 2st.txt";
    read FILENAME;
    
    if [[ $FILENAME == *.txt ]];
      then
        if [ -f $FILENAME ]; 
        then
            tail -n +4 $FILENAME | head -n -3 | sort -k 6,6 |awk '$4 < 100 { next } { print }' | awk '$4 < 100 { next } { print }' |tail -n 16 > "InterestingTM"$FILENAME;
        else
            echo "File $FILENAME does not exist.";
        fi
    else
        echo "Please select .txt file";
    fi
    cd ../scripts;
fi

# ==============================================================================
# Profile of TM in provided file
# ==============================================================================

if [[ "$PROFILE" -eq "1" ]];
    then
    cd ../resultText;
    echo "Please insert filtered file with machines that will make the profile: Ex: InterestingTM2st.txt";
    read FILENAME;
    if [[ $FILENAME == *.txt ]]
      then
        if [ -f $FILENAME ]; then
            echo "Please insert #States: Ex: 2"
            read STATE;
            echo "Please insert #Alphabet: Ex: 2"
            read ALPHABET;

            while read p; do
                TM=$(echo $p | awk '{ print $1;}');
                K=$(echo $p | awk '{ print $2;}');
                #NUMBERITERATION=$(echo $p | awk '{ print $3;}');
                NUMBERITERATION=1001;
                bash ../scripts/normalProfile.sh $TM $STATE $ALPHABET $NUMBERITERATION $K;
            done <$FILENAME
        
            Folder=${STATE}St${ALPHABET}AlphTM/;
            DIRECTORY=${SavePath}${Folder};
            cd ${DIRECTORY};
            pdfunite Profile*.pdf AllNormProfile${STATE}St${ALPHABET}AlphTM.pdf;
            rm Profile*.pdf;
            cd ../..;
        fi
    fi
    cd ./scripts;
fi

# ==============================================================================
# Dynamical Temporal Profile of TM from provided file
# ==============================================================================

if [[ "$DYNAMICPROFILE" -eq "1" ]];
    then
    cd ../resultText;
    echo "Please insert file with the turing Machine Indexes which you wish to create a dynamic profile: Ex: InterestingTM2st.txt";
    read FILENAME;
    if [[ $FILENAME == *.txt ]]
      then
        if [ -f $FILENAME ]; then
            echo "Please insert #States: Ex: 2"
            read STATE;
            echo "Please insert #Alphabet: Ex: 2"
            read ALPHABET;

            while read p; do 
                TM=$(echo $p | awk '{ print $1;}');
                K=$(echo $p | awk '{ print $2;}');
                NUMBERITERATION=1001; # $(echo $p | awk '{ print $3;}');
                bash ../scripts/dynamicProfile.sh $TM $STATE $ALPHABET $NUMBERITERATION $K;
            done <$FILENAME
        fi
        Folder=${STATE}St${ALPHABET}AlphTM/;
        DIRECTORY=${SavePath}${Folder};
        cd ${DIRECTORY};
        pdfunite DynProfile*.pdf AllDynProfile${STATE}St${ALPHABET}AlphTM.pdf;
        rm DynProfile*.pdf;
        cd ../..;
    fi
    cd ./scripts;
fi
