#!/bin/bash
#
# ==============================================================================
# Download Results in order to plot graphics
# ==============================================================================

cd scripts/;

chmod +x *.sh;
echo "Downloading dataset...";
bash downloadResults.sh;
echo "Intalling tools required for plots dataset...";
bash installTools.sh;
echo "Recreating plots Profiles and Dynamic Profiles...";
bash reprArticlePlot.sh 1 1 0 0 0 0;
echo "Recreating Edition and permutation plots...";
bash reprArticlePlot.sh 0 0 1 1 1 1;
echo "Recreating plots of Cardinality Growth and TMs...";
bash processResults.sh 0 1 1 1 1 1 1 1;

cd ..;
