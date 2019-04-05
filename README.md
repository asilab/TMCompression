<p align="center">
<img src="icons/logo.png" alt="TMCompression" width="600" border="0" /></p>
<br>
<p align="center">
</p>

# Simple Turing Machines, Statistic Complexity vs Algorithmic Complexity
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/9d4bb3ca2a0b4dd7a44503fc405b5b1c)](https://app.codacy.com/app/jorgeMFS/TMCompression?utm_source=github.com&utm_medium=referral&utm_content=jorgeMFS/TMCompression&utm_campaign=Badge_Grade_Dashboard)
[![Build Status](https://travis-ci.org/jorgeMFS/TMCompression.svg?branch=master)](https://travis-ci.org/jorgeMFS/TMCompression)
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](LICENSE)

## INSTALL
Get TMCompression and make the project, using:
```bash
git clone https://github.com/jorgeMFS/TMCompression.git;
cd TMCompression;
make;
make ioStNormalize;
make TMsimulator;
```
    
## TMCompression Repository Organization
Folder organization:
```Array.<string>
 ./src : Source Code of the TMCompression Program;
 ./val : Source Code of program used in Turing Tape Validation;
 ./scripts : Bash Scripts to Process Results and plot them
 ./resultText : Textual results obtained from the usage of TMCompression;
 ./resultPlots : Plots of some results obtained;
 ./profiles : Normal Profiles and Dynamic Temporal Profiles of Turing Machine Tapes.
```

## RUN TMCompression
There are many ways to run this program see help for clarification :

```bash
./tm --help;
```

## RECREATE PLOTS IN ARTICLE
To recreate the plots shown in the article (bellow example):

```bash
chmod +x run.sh;
bash run.sh;
```
<b>Profile Plots:</b>

![alt-text-1](icons/NormalProfilesArticle.png "Normal Profile" ) 
![alt-text-2](icons/DynamicProfilesArticle.png "DynamicProfile")

<b>TMs Plots:</b>


<p align="center">
<img src="icons/TMs.png" alt="TMs" width="600" border="0" /></p>
<br>
<p align="center">
</p>

## RUN OTHER SCRIPTS
There are two main scripts:
```bash
./processResults.sh : "Plots graphics shown in Folder ./resultPlot"
./filteringResults.sh :"Plots Profiles shown in Folder ./profiles"
```

There are many ways to the scripts, see help for clarification:

```bash
bash scripts/processResults.sh;
bash scripts/filteringResults.sh;
```

## CITE
Please cite the followings, if you use TMCompression:

```Array.<string>
- Processing...
```
## ISSUES
Please let us know if there is any
[issues](https://github.com/jorgeMFS/TMCompression/issues).

## LICENSE
TMCompression is under GPL v3 license. For more information, click
[here](http://www.gnu.org/licenses/gpl-3.0.html).
