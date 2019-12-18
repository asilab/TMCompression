/**
    parseArgs.cpp
    Purpose: Parse input arguments

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#include <getopt.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include "util.h"
#include "parseArgs.h"
#include "tm.h"
#include "tmId.h"
#include "randomString.h"
#include "stateMatrixParser.h"


Args parseArgs (int argc, char **argv){
    Args argument {};    
    opterr = 0;
    static int mutate_flag;
    static int verbose_flag;
    static int best_flag;
    static int replicate_flag;
    static int tm_verbose_flag;
    static int tm_profile_flag;
    static int tm_number_growth_flag;
    static int tm_dynamical_profile_flag;
    static int tm_print_flag;
    static int StMatrix_flag;
    static int mutate_virus_flag;
    static int method_I_plot_flag;
    static int method_II_plot_flag;
    static int method_III_plot_flag;
    static int method_II_growth_plot_flag;
    static int method_III_growth_plot_flag;
    static int tm_rule_profile_flag;
    static int tm_rule_flag;
    static int tm_print_rule_flag;
    static int graph_method_II;
    char *end;
    TmId correctInput;
    while (1)
    {
        static struct option long_options[] =
        {
            {"verbose",   no_argument,      &verbose_flag, 1},
            {"brief",     no_argument,      &verbose_flag, 0},
            {"tmverbose",   no_argument,      &tm_verbose_flag, 1},
            {"replicate",      no_argument,      &replicate_flag, 1},
            {"tmgrowth",      no_argument,      &tm_number_growth_flag, 1},
            {"dynprofile",      no_argument,      &tm_dynamical_profile_flag, 1},
            {"profile", no_argument, &tm_profile_flag,1},
            {"ruleProfile",no_argument, &tm_rule_profile_flag, 1},
            {"ruleMetrics",no_argument, &tm_rule_flag, 1},
            {"printTape", no_argument, &tm_print_flag,1},
            {"ruleTape", no_argument, &tm_print_rule_flag,1},
            {"StMatrix", no_argument, &StMatrix_flag,1},
            
            {"MethodI", no_argument, &method_I_plot_flag,1},
            {"MethodII", no_argument, &method_II_plot_flag,1},
            {"MethodIII", no_argument, &method_III_plot_flag,1},
            {"MethodIIGrowth", no_argument, &method_II_growth_plot_flag,1},
            {"MethodIIIGrowth", no_argument, &method_III_growth_plot_flag,1},
            

            {"best", no_argument, &best_flag,1},
            {"3DgraphMethodII", no_argument, &graph_method_II,1},
            {"mutate", no_argument, &mutate_flag,1},
            {"mutateVirus", no_argument, &mutate_virus_flag,1},
            {"help",      no_argument,      0, 'h'},
            {"version",      no_argument,      0, 'v'},
            
            {"number_states",     required_argument,      0 , 's'},
            {"alphabet_size",  required_argument, 0, 'a'},
            {"iterations",  required_argument, 0, 'i'},
            {"context",  required_argument, 0, 'k'},
            {"tm", optional_argument, 0, 't'},
            {"tm_it", optional_argument, 0, 'g'},
            {"strategy", optional_argument, 0, 'S'},
            {"n", optional_argument, 0, 'N'},
            {"jobs", optional_argument, 0, 'j'},
            {"state_matrix",     required_argument,      0 , 'm'},
            {NULL, 0, NULL, 0}
        };
        int option_index = 0;

        int c = getopt_long (argc, argv, "s:a:i:k:t:S:N:j:m:g:hv",
                        long_options, &option_index);

        if (c == -1)
        break;
        
        switch (c)
        {
        case 0:
            if (long_options[option_index].flag != 0)
            break;
            printf ("option %s", long_options[option_index].name);

            if (optarg)
            printf (" with arg %s", optarg);
            printf ("\n");
            break;

        case 'h':
            std::cout << std::endl << "-----------------------------------------------------------------------------" << std::endl;
            std::cout << "Program that creates Turing machines and Measures its Statistical Complexity." << std::endl;
            std::cout << "-----------------------------------------------------------------------------" << std::endl<<std::endl;

            std::cout << "Arguments to set flags:" << std::endl<<std::endl;
            std::cout << "--verbose" << "\t" << "Indicates programs that will receive inputs in a verbose form." << std::endl << std::endl;
            std::cout << "--brief" << "\t" << "Indicates programs that will receive inputs in a brief form." << std::endl << std::endl;
            std::cout << "--tmverbose" << "\t" << "Indicates programs that tm output will be send to the user." << std::endl << std::endl;
            std::cout << "--tmgrowth" << "\t" 
            << "Indicates programs that output a list of Turing machines with an increase in the number of states and a alphabet size of 2" 
            << std::endl<< std::endl;
            std::cout << "--replicate" << "\t" 
            << "Indicates programs that will replicate experiment to determine the best k and it for a given number of states and alphabet size." 
            << std::endl<< std::endl;
            std::cout << "--profile" << "\t" 
            << "Indicates programs that will receive through the tm number through the flag tm and will create a profile of that turing" 
            << std::endl<< std::endl;
            std::cout << "--dynprofile" << "\t" 
            << "Indicates programs that will receive through the tm number through the flag tm and will create a dynamical temporal profile of that turing" 
            << std::endl<< std::endl;
            std::cout << "--StMatrix" << "\t" 
            << "Indicates programs to print the StateMatrix of a given TMs" 
            << std::endl<< std::endl;
            std::cout << "--ruleMetrics" << "\t" 
            << "Indicates programs to compute the rule metrics of a given TMs" 
            << std::endl<< std::endl;

            std::cout << "--ruleProfile" << "\t" 
            << "Indicates programs to create a Compression profile of the rules for a given Turing Machine" 
            << std::endl<< std::endl;

            std::cout << "--mutate" << "\t" 
            << "Indicates programs to print the nc of the mutation of a string (starting with all zeros and ending with all ones) and performing mutations until its 100% mutated" 
            << std::endl<< std::endl;
            std::cout << "--mutateVirus" << "\t" 
            << "Indicates programs perform the edition and permutation of a virus DNA sequence and print NC results" 
            << std::endl<< std::endl;
            std::cout << "--MethodI" << "\t" 
            << "Indicates programs to recreate similar list of results used in plots of the article using MethodI" 
            << std::endl<< std::endl;
            std::cout << "--MethodII" << "\t" 
            << "Indicates programs to recreate similar list of results used in plots of the article using MethodII" 
            << std::endl<< std::endl;
            std::cout << "--MethodIII" << "\t" 
            << "Indicates programs to recreate similar list of results used in plots of the article using MethodIII" 
            << std::endl<< std::endl;
            std::cout << "--3DgraphMethodII" << "\t" 
            << "Indicates programs to recreate similar list of results used in 3D plots of the article using MethodII" 
            << std::endl<< std::endl;
            
            std::cout << "Mandatory  Arguments:"<< std::endl << std::endl;
            std::cout << "-s" << ", " <<"--number_states" << "\t" << "Number of States the Turing Machine has."<< std::endl << std::endl;
            std::cout << "-a" << ", " << "--alphabet_size" << "\t" << "Alphabet size the Turing Machine considers." << std::endl<<std::endl;
            std::cout << "-i" << ", " << "--iterations" << "\t " << "Number of iterations the Turing Machine makes in the tape."<< std::endl<<std::endl;
            std::cout << "-k" << ", " << "--context" << "\t" << "k indexes to consider as a context to fill the Markov Table." <<std::endl<<std::endl;
            std::cout << "-t" << ", " << "--tm" << "\t" << "Speciffy turing to obtain results, can only be activated with --profile flag." <<std::endl<<std::endl;

            std::cout << "Other Optional Arguments:" << std::endl<< std::endl;
            std::cout << "-S" << ", " << "--strategy" << "\t" << "Turing Machine traversal strategy (default: sequential)"<< std::endl << std::endl;
            std::cout << "-N" << ", " << "\t" << "Number of Turing Machines to traverse" << std::endl << std::endl;
            std::cout << "-v" << ", " << "--version" << "\t" << "Outputs the version of the program." << std::endl <<std::endl;
            std::cout << "-h" << ", " << "--help" << "\t" << "Describes program." <<std::endl<<std::endl;
            std::cout << "-----------------------------------------------------------------------------" << std::endl;
            std::cout << "Examples:" << std::endl;
            std::cout << "-----------------------------------------------------------------------------" << std::endl;
            std::cout << "Run all tms" << std::endl;
            std::cout << "./tm -s 2 -a 2 -i 10 -k 1 " << std::endl;
            std::cout << "./tm --brief -s 2 -a 2 -i 10 -k 1" << std::endl;
            std::cout << "./tm --verbose --number_states=2 --alphabet_size=2 --iterations=20 --context=2" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout << "Run all tms with multithreads" << std::endl;
            std::cout << "./tm -s 2 -a 2 -i 10 -k 1 -j 7" << std::endl;
            std::cout << "./tm --brief -s 2 -a 2 -i 10 -k 1 -j 7" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout << "Strategies of running TM Machines" << std::endl;
            std::cout <<"By default strategy is Sequential:"<< std::endl;
            std::cout << "./tm --brief -s 2 -a 2 -i 10 -k 1 -j 7" << std::endl;
            std::cout << "./tm --brief -s 2 -a 2 -i 10 -k 1 -N 10 -j 4 -S sequential" << std::endl;
            std::cout <<"Monte Carlo:"<< std::endl;
            std::cout << "./tm --brief -s 2 -a 2 -i 10 -k 1 -N 10 -j 4 -S monte_carlo" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout << "Run specific tm and obtain profile:" << std::endl;
            std::cout << "./tm --brief --profile -s 2 -a 2 -i 100 -k 2 -t 5" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout << "Run specific tm and obtain dynamical temporal profile:" << std::endl;
            std::cout << "./tm --brief --dynprofile -s 2 -a 2 -i 100 -k 2 -t 5 "<< std::endl;
            std::cout << "----------------" << std::endl;
            std::cout << "Run specific tm and obtain their Rule Compression Profile:" << std::endl;
            std::cout << "./tm --brief --ruleMetrics -s 2 -a 2 -i 100 -t 5" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout << "Replicate k and it determination:" << std::endl;
            std::cout << "./tm --brief --replicate -s 2 -a 2 -j 10" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout << "turing machine growth with alphabet size of 2 and increase in state cardinality:" << std::endl;
            std::cout << "./tm --tmgrowth" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout <<"Run specific tm and print tape" << std::endl;
            std::cout << "./tm --brief --printTape -s 2 -a 2 -i 100 -t 1"<< std::endl;
            std::cout << "----------------" << std::endl;
            std::cout <<"Run StMatrix of the tm" << std::endl;
            std::cout << "./tm --brief --StMatrix -s 2 -a 2 -t 1"<< std::endl;
            std::cout << "----------------" << std::endl;
            std::cout <<"Obtain nc of the substitutions and permutations of a string " << std::endl;
            std::cout <<"./tm --mutate" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout <<"Obtain nc of Virus genome sequence with substitutions and permutations" << std::endl;
            std::cout <<"echo \"./resultText/Parvovirus_virus_genome.txt\" | ./tm --mutateVirus" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout <<"Obtain list of graph of Method I" << std::endl;
            std::cout <<"./tm --MethodI" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout <<"Obtain list of graph of Method II" << std::endl;
            std::cout <<"./tm --MethodII" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout <<"Obtain list of graph of Method III" << std::endl;
            std::cout <<"./tm --MethodIII" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout <<"Obtain list of 3d graphs of Method II" << std::endl;
            std::cout <<"./tm --3DgraphMethodII" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout <<"Obtain list of graph growth for Method II" << std::endl;
            std::cout <<"./tm --MethodIIGrowth" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout <<"Obtain list of graph growth for Method III" << std::endl;
            std::cout <<"./tm --MethodIIGrowth" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout <<"Apply Method III for a given state, alphabet,tm iterations and tape iterations" << std::endl;
            std::cout <<"./tm --best -s 2 -a 2 -i 1000 -g 1000"<< std::endl;
            exit (0);

        case 'v':
            std::cout << "Relative Turing Machine Version 0.1" << std::endl<<std::endl;
            exit (0);
        case 's':
            {
            correctInput = strtol(optarg, &end, 10);
            if (*end != '\0') {
                std::cerr << "Invalid input for -s/--number_states.\n";
                exit(0);
            }
            else if (correctInput<=0){
                std::cerr << "-s/--number_states value was set to " << correctInput <<", must be an int larger than 0.\n";
                exit(0);
            }
            else argument.states = correctInput;
            break;
            }

        case 'a':
            {
            correctInput = strtol(optarg, &end, 10);
            if (*end != '\0') {
                std::cerr << "Invalid input for -a/--alphabet_size.\n";
                exit(0);
            }
            else if (correctInput<=0){
                std::cerr << "-a/--alphabet_size value was set to " << correctInput <<", must be an int larger than 0.\n";
                exit(0);
            }
            else argument.alphabet_size = correctInput;
            break;
            }

        case 'i':
            {
            correctInput = strtol(optarg, &end, 10);
            if (*end != '\0') {
                std::cerr << "Invalid input for -i/--iterations.\n";
                exit(0);
            }
            else if (correctInput<=0){
                std::cerr << "-i/--iterations value was set to " << correctInput <<", must be an int larger than 0.\n";
                exit(0);
            }
            else argument.numIt = correctInput;
            break;
        }
        case 'g':
            {
            correctInput = strtol(optarg, &end, 10);
            if (*end != '\0') {
                std::cerr << "Invalid input for -g/--tm_it.\n";
                exit(0);
            }
            else if (correctInput<=0){
                std::cerr << "-g/--tm_it value was set to " << correctInput <<", must be an int larger than 0.\n";
                exit(0);
            }
            else argument.tmIt = correctInput;
            break;
        }
        case 'k':
        {   
            std::pair<unsigned int,unsigned int> k_limits;
            std::vector<unsigned int> k_values;
            if (std::strchr(optarg, ':')){
                auto token = std::strtok (optarg," :");
                unsigned int counter=0;
                
                while (token != NULL)
                {
                    if (counter>1){
                        std::cerr << "Invalid input for -k/--context." << std::endl <<
                        "If you want to provide a range for k " <<
                         "please provide -k/--context with 2 elements separated by \":\".\n" <<
                         "Example: -k 2:4"<< std::endl;
                        exit(0);
                    }
                    else{
                        correctInput = strtol(token, &end, 10);
                        if (*end != '\0') {
                            std::cerr << "Invalid input for -k/--context.\n";
                            exit(0);
                        }
                        else if (correctInput<=0){
                            std::cerr << "-k/--context value was set to " << correctInput <<", must be an int larger than 0.\n";
                            exit(0);
                        }
                        else {
                            if (counter==0) k_limits.first=correctInput;
                            else if (counter==1) k_limits.second=correctInput;
                        };
                    }
                    token = strtok (NULL, ":");
                    ++counter;
                }
            }            
            else{
                correctInput = strtol(optarg, &end, 10);
                if (*end != '\0') {
                    std::cerr << "Invalid input for -k/--context.\n";
                    exit(0);
                    }
                else if (correctInput<=0){
                    std::cerr << "-k/--context value was set to " << correctInput <<", must be an int larger than 0.\n";
                    exit(0);
                }
                else {
                    k_limits.first = correctInput;
                    k_limits.second = correctInput; 
                }
            }

            if (k_limits.first<=k_limits.second){
                for (auto it=k_limits.first; it!=k_limits.second+1;++it){
                    k_values.push_back(it);
                }
            }
            argument.k = k_values;
            break;
        }
        case 't':
        {
          	std::string str(optarg);
            TmId tmInput = string_to_uint128(str);
            argument.tm.first = tmInput;
            argument.tm.second = true;
            break;
        }
        case 'j':
        {
            correctInput = strtol(optarg, &end, 10);
            if (*end != '\0') {
                std::cerr << "Invalid input for -j/--jobs." << std::endl;
                exit(0);
            }
            else if (correctInput<=0){
                std::cerr << "-j/--jobs value was set to " << correctInput <<", must be an int larger than 0.\n";
                exit(0);
            }
            else argument.jobs = correctInput;
            break;
        }
        case 'm':
        {   std::string srt(optarg);
            argument.state_matrix_string = srt;
            break;
        }
        case 'S':
        {
            if (std::strcmp(optarg, "sequential") == 0) {
                argument.strategy = TraversalStrategy::SEQUENTIAL;
            } else if (std::strcmp(optarg, "monte_carlo") == 0) {
                argument.strategy = TraversalStrategy::MONTE_CARLO;
            } else {
                std::cerr << "-S/--strategy must be either `sequential` or `monte_carlo`." << std::endl;
                exit(0);
            }
            break;
        }
        case 'N':
        {
            auto parsed = strtoull(optarg, &end, 10);
            if (*end != '\0') {
                std::cerr << "Invalid input for -N.\n";
                exit(0);
            }
            argument.n = parsed;
            break;
        }
        case '?':
            break;

        default:
            abort ();
        }
    }

    if (verbose_flag) {
        std::cerr << "verbose flag is set" << std::endl;
    }

     if (tm_verbose_flag) {
        std::cerr << "tm verbose flag is set, output will be send to the user" << std::endl;
        argument.verbose = true;
    }

    if(graph_method_II){
        evolve_multiple_tms_graph(3200,8000,10,2);
        exit(0);
    }

    if(method_I_plot_flag){
        evolve_multiple_tms(200,100,10,2);
        exit(0);

    }
    if(method_II_plot_flag){//change
        evolve_multiple_tms2(200,1200000,5000,10,2);
        //evolve_multiple_tms2(2000,1000, 5000,10,2);
        exit(0);
    }
    if(method_III_plot_flag){ //change
        //repeats, tmit, tapeit, states, alphabet
        evolve_multiple_tms3(200,1000,5000,10,2);
        exit(0);
    }

    if(method_II_growth_plot_flag){ //change
        //repeats, tmit, tapeit, states, alphabet
        growth_plot_tms2(200,1200000,5000,10,2);
        exit(0);
    }
    if(method_III_growth_plot_flag){ //change
        //repeats, tmit, tapeit, states, alphabet
        growth_plot_tms3(200,1000,5000,10,2);
        exit(0);
    }

    if(best_flag && argument.states!=0 && argument.alphabet_size!=0 && argument.numIt!=0 && argument.tmIt!=0){
        evolve_bb_tm(argument.states, argument.alphabet_size,argument.tmIt, argument.numIt, true, false);
         exit(0);
    }
    
    

    if (optind < argc)
    {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
        printf ("%s ", argv[optind++]);
        putchar ('\n');
    }
    if (mutate_virus_flag && argument.states==0 && argument.alphabet_size==0 && argument.numIt==0 && argument.k.empty() && argument.tm.second==false){
        std::cerr << "Editing/Permutation Virus DNA sequence and obtaining NC results..." <<std::endl;
        
        std::string virus_file_path;
        std::cerr << "Insert path of genome sequence :"; std::cin >> virus_file_path;
        nc_substitution_permutate_sequence(true, virus_file_path);

        exit(0);
    }
    if (mutate_flag && argument.states==0 && argument.alphabet_size==0 && argument.numIt==0 && argument.k.empty() && argument.tm.second==false){
        std::cerr << "Editing string and obtaining NC results..." <<std::endl;
        nc_substitution_permutate_sequence(false, "");
        exit(0);
    }
    if (tm_number_growth_flag && argument.states==0 && argument.alphabet_size==0 && argument.numIt==0 && argument.k.empty() && argument.tm.second==false){
        std::cerr << "TM growth for alphabet = 2 and Max number of states = 100" <<std::endl;
        tm_growth_with_cardinality(100);
        exit(0);
    }
    else if((argument.states!=0 && argument.alphabet_size!=0 && argument.numIt!=0 && argument.k.empty() && argument.tm.second) && tm_print_flag==1 && tm_profile_flag==0 && replicate_flag==0 && tm_number_growth_flag==0){
            tm_print_tape(argument.states,
                     argument.alphabet_size,
                     argument.numIt,
                     argument.tm.first);
            exit(0);

    }
    else if((argument.states!=0 && argument.alphabet_size!=0 && argument.numIt!=0 && argument.k.empty() && argument.tm.second) && tm_rule_flag==1 && tm_profile_flag==0 && replicate_flag==0 && tm_number_growth_flag==0){
            tm_rules_metrics(argument.states,
                     argument.alphabet_size,
                     argument.numIt,
                     argument.tm.first);
            exit(0);
    }
    else if((argument.states!=0 && argument.alphabet_size!=0 && argument.numIt!=0 && argument.k.empty() && argument.tm.second) && tm_print_rule_flag==1 && tm_rule_flag==0 && tm_profile_flag==0 && replicate_flag==0 && tm_number_growth_flag==0){
            tm_print_rules(argument.states,
                argument.alphabet_size,
                argument.numIt,
                argument.tm.first);
            exit(0);
    }
    else if ( (argument.states!=0 || argument.alphabet_size!=0 || argument.numIt!=0 || (!argument.k.empty()) || argument.jobs!=0 ) && tm_number_growth_flag ){
        std::cerr << "Please fill all the required arguments in order to perform the tm growth" <<std::endl;
        std::cerr << "Example: ./tm --tmgrowth" << std::endl;
        exit(0);
    }


    else if((argument.states==0 || argument.alphabet_size==0 || argument.numIt==0 || argument.k.empty() || argument.tm.second==false ) && tm_profile_flag==1 && replicate_flag==0 && tm_number_growth_flag==0){
        std::cerr << "Please fill all the required arguments" <<std::endl;
        exit(0);
    }
    else if(argument.tm.second && tm_rule_profile_flag==0 && tm_profile_flag==0 && tm_dynamical_profile_flag==0 && StMatrix_flag==0 && tm_print_flag==0 && replicate_flag==0 ){
        std::cerr << "You can only provide tm with the --profile / --dynprofile / --ruleProfile / --ruleMetrics" <<std::endl;
        std::cerr << "Example: ./tm --brief --profile -s 2 -a 2 -i 100 -k 2 -t 5" << std::endl;
        std::cerr << "Example: ./tm --brief --dynprofile -s 2 -a 2 -i 100 -k 2 -t 5" << std::endl;
        std::cerr << "Example: ./tm --brief --ruleProfile -s 2 -a 2 -i 100 -k 2 -t 5" << std::endl;
        std::cerr << "Example: ./tm --brief --ruleMetrics -s 2 -a 2 -i 100 -t 5" << std::endl;

        exit(0);
    }

    else if ( (argument.states!=0 && argument.alphabet_size!=0 && argument.numIt!=0 && (argument.k.size()==1 ) && argument.tm.second) && tm_profile_flag==0 && tm_dynamical_profile_flag==1 && replicate_flag==0){
        tm_dynamical_profile(argument.states,
                argument.alphabet_size,
                argument.numIt,
                argument.k.front(),
                argument.tm.first , 5);
        exit(0);

    }
    else if ( (argument.states!=0 || argument.alphabet_size!=0|| argument.tm.second) && tm_profile_flag==0 && replicate_flag==0 && tm_dynamical_profile_flag==0 && StMatrix_flag==1){    
        tm_print_state_matrix(argument.states,
                     argument.alphabet_size,
                     argument.tm.first);
        exit(0);

    }
    else if ( (argument.states!=0 || argument.alphabet_size!=0 || argument.numIt!=0 || (argument.k.size()==1 ) || argument.tm.second ) && tm_profile_flag==1 && replicate_flag==0 && tm_dynamical_profile_flag==0){
        tm_profile(argument.states,
                argument.alphabet_size,
                argument.numIt,
                argument.k.front(),
                argument.tm.first, 5);
        exit(0);
    }
    else if ( (argument.states!=0 || argument.alphabet_size!=0 || argument.numIt!=0 || (argument.k.size()==1 ) || argument.tm.second ) && tm_rule_profile_flag==1 && replicate_flag==0 && tm_dynamical_profile_flag==0){
        tm_profile_rules(argument.states,
                argument.alphabet_size,
                argument.numIt,
                argument.k.front(),
                argument.tm.first, 5);
        exit(0);
    }
    
    else if ( (argument.states==0 || argument.alphabet_size==0 || argument.jobs==0 || tm_profile_flag) && replicate_flag ){
        std::cerr << "Please fill all the required arguments in order to perform a replication" <<std::endl;
        std::cerr << "Example: ./tm --brief --replicate -s 2 -a 2 -j 10" << std::endl;
        exit(0);
    }

    else if ( (argument.states==0 || argument.alphabet_size==0 || argument.numIt==0 || argument.k.empty()) && replicate_flag==0 && tm_profile_flag==0) 
    {
        std::cerr << "Please fill all the required arguments" <<std::endl;
        exit(0);
    }
    else if ( (argument.numIt==0 || argument.k.empty()) &&  argument.states!=0 && argument.alphabet_size!=0 && replicate_flag && argument.jobs!=0)
    { 
        printf ("replication flag is set, the system will run for alphabet_size = %zu and states = %zu, number of iterations ={100, 1000, 10000} and k=[2,10] using threads=%u\n"
        ,argument.alphabet_size,argument.states,argument.jobs);
        printf ("\n");
        ktm_multicore(argument.states, argument.alphabet_size,argument.jobs);
        exit(0);
    }
    if (argument.k.size()>1){
        printf ("states = %zu, alphabet_size = %zu, number of iterations = %u , k = %u:%u\n",
        argument.states, argument.alphabet_size, argument.numIt, argument.k.front(), argument.k.back());
    }
    else if (argument.k.size()==1){
        printf ("states = %zu, alphabet_size = %zu, number of iterations = %u , k = %u\n",
        argument.states, argument.alphabet_size, argument.numIt, argument.k.front());
    }

    for (auto kval: argument.k){
        if(ipow<TmId>(argument.alphabet_size, kval) >= ipow<TmId>(2,28)){
            fprintf (stderr, "k/context (%u) and Alphabet size/a (%zu) is too large..\n", kval, argument.alphabet_size);
            fprintf (stderr, " please consider a size of a^k (%zu^%u) smaller than 2^28..\n", argument.alphabet_size,kval);
            exit(0);
        }
    }

    return argument;
}

void printArgs(Args arguments){
    std::cout << "states = " << arguments.states << std::endl;
    std::cout << "alphabet_size = " << arguments.alphabet_size << std::endl;
    std::cout << "threshold = " << arguments.threshold << std::endl;
    std::cout << "number Iterations = " << arguments.numIt << std::endl;
    std::cout << "State Matrix String = " << arguments.state_matrix_string << std::endl;

    if (arguments.k.size()>1){
        std::cout << "k = " << arguments.k.front() <<  ":" << arguments.k.back() << std::endl;
    }
    else if (arguments.k.size()==1){
        std::cout << "k = " << arguments.k.front() << std::endl;
    }
    std::cout << "tm = " << arguments.tm.first << std::endl;
    if(arguments.strategy == TraversalStrategy::SEQUENTIAL){
        std::cout << "strategy = " << "Sequential"  << std::endl; //might require twerks
    }
    else if(arguments.strategy == TraversalStrategy::MONTE_CARLO){
        std::cout << "strategy = " << "Monte Carlo"  << std::endl;
    }
    std::cout << "n = " << arguments.n << std::endl;
    std::cout << "jobs = " << arguments.jobs << std::endl;
    std::cout << "verbose = " << arguments.verbose << std::endl;
}