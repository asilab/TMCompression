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

-----------------------------------------------------------------------------
Program that creates Turing machines and Measures its Statistical Complexity.
-----------------------------------------------------------------------------

Arguments to set flags:

--verbose	Indicates programs that will receive inputs in a verbose form.

--brief	        Indicates programs that will receive inputs in a brief form.

--tmverbose	Indicates programs that tm output will be send to the user.

--tmgrowth	Indicates programs that output a list of Turing machines with an increase in the number of states and a alphabet size of 2

--replicate	Indicates programs that will replicate experiment to determine the best k and it for a given number of states and alphabet size.

--profile	Indicates programs that will receive through the tm number through the flag tm and will create a profile of that turing

--dynprofile	Indicates programs that will receive through the tm number through the flag tm and will create a dynamical temporal profile of that turing

--mutate        Indicates programs to print the nc of the mutation of a string starting with all zeros and performing mutations until its 100% mutated

--StMatrix	Indicates programs to print the StateMatrix of a given TMs

Mandatory  Arguments:

-s, --number_states	Number of States the Turing Machine has.

-a, --alphabet_size	Alphabet size the Turing Machine considers.

-i, --iterations	 Number of iterations the Turing Machine makes in the tape.

-k, --context	k indexes to consider as a context to fill the Markov Table.

-t, --tm	Specifies turing to obtain results, can only be activated with --profile flag.

Other Optional Arguments:

-S, --strategy	Turing Machine traversal strategy (default: sequential)

-N, 	Number of Turing Machines to traverse

-v, --version	Outputs the version of the program.

-h, --help	Describes program.

-----------------------------------------------------------------------------
Examples:
-----------------------------------------------------------------------------
Run all tms
./tm -s 2 -a 2 -i 10 -k 1
./tm --brief -s 2 -a 2 -i 10 -k 1
./tm --verbose --number_states=2 --alphabet_size=2 --iterations=20 --context=2
----------------
Run all tms with multithreads
./tm -s 2 -a 2 -i 10 -k 1 -j 7
./tm --brief -s 2 -a 2 -i 10 -k 1 -j 7
----------------
Strategies of running TM Machines
By default strategy is Sequential:
./tm --brief -s 2 -a 2 -i 10 -k 1 -j 7
./tm --brief -s 2 -a 2 -i 10 -k 1 -N 10 -j 4 -S sequential
Monte Carlo:
./tm --brief -s 2 -a 2 -i 10 -k 1 -N 10 -j 4 -S monte_carlo
----------------
Run specific tm and obtain profile:
./tm --brief --profile -s 2 -a 2 -i 100 -k 2 -t 5
----------------
Run specific tm and obtain dynamical temporal profile:
./tm --brief --dynprofile -s 2 -a 2 -i 100 -k 2 -t 5 
----------------
Replicate k and it determination:
./tm --brief --replicate -s 2 -a 2 -j 10
----------------
turing machine growth with alphabet size of 2 and increase in state cardinality:
./tm --tmgrowth
----------------
Run specific tm and print tape
./tm --brief --printTape -s 2 -a 2 -i 100 -t 1
Run StMatrix of the tm
./tm --brief --StMatrix -s 2 -a 2 -t 1
----------------
Mutate (0-100%) string of all zeros specific tm and print tape
./tm --mutate

```

## RECREATE PLOTS IN ARTICLE
To recreate the plots shown in the article (bellow example):

```bash
chmod +x run.sh;
bash run.sh;
```
<b>Profile Plots:</b>
<p align="center">
<img src="icons/profiles.png" alt="TMs" width="500" border="0" /></p>
<br>
<p align="center">
</p>
<p align="center">
<img src="icons/string.png" alt="TMs" width="500" border="0" /></p>
<br>
<p align="center">
</p>

<b>TMs Plots:</b>
<p align="center">
<img src="icons/TMs.png" alt="TMs" width="500" border="0" /></p>
<br>
<p align="center">
</p>

Note: This downloads the files Containing the results from running all TMs for a given State and Alphabet Cardinality, since this can take from several minutes to several days. If you wish to recreate the Results use TM program. Example:

```bash
./tm --brief -s 2 -a 4 -i 50000 -k 2:10 -N 30000000 -j 20 -S monte_carlo > 2sts4alp.txt;
```

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
