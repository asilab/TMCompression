#!/bin/bash
#

function run_nc_genome {
    DIR=$(dirname "$1");
    filename=$(basename -- "$1");
    extension="${filename##*.}";
    filename="${filename%.*}_nc.txt ";
    echo "$1" | ../tm --mutateVirus > "${DIR}/${filename}";  # Do something else
}

find ../virus_genomes/ -type f -name "*genome.txt" | while read txt; do
    run_nc_genome "$txt" &   
done

