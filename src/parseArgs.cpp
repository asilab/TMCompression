#include <getopt.h>
#include <iostream>

#include "markovTable.h"
#include "parseArgs.h"


Args parseArgs (int argc, char **argv){
    Args argument{0,0,0,0,0};    
    int c;
    opterr = 0;

    static int verbose_flag;
    char *end;
    int correctInput;
    while (1)
    {
        static struct option long_options[] =
        {
            {"verbose",   no_argument,      &verbose_flag, 1},
            {"brief",     no_argument,      &verbose_flag, 0},
            {"help",      no_argument,      0, 'h'},
            {"version",      no_argument,      0, 'v'},
            {"number_states",     required_argument,      0 , 's'},
            {"alphabet_size",  required_argument, 0, 'a'},
            {"iterations",  required_argument, 0, 'i'},
            {"context",  required_argument, 0, 'k'},
            {NULL, 0, NULL, 0}
        };
        int option_index = 0;

        c = getopt_long (argc, argv, "s:a:i:k:hv",
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
            std::cout << "Program that creates a relative turing machine." << std::endl<<std::endl;
            std::cout << "Arguments to set flags:" << std::endl;
            std::cout << "--verbose" << "\t" << "Indicates programs that will receive inputs in a verbose form." << std::endl;
            std::cout << "--brief" << "\t" << "Indicates programs that will receive inputs in a brief form." << std::endl<< std::endl;

            std::cout << "Mandatory  Arguments:" << std::endl;
            std::cout << "-s" << ", " <<"--number_states" << "\t" << "Number of States the Turing Machine has." << std::endl;
            std::cout << "-a" << ", " << "--alphabet_size" << "\t" << "Alphabet size the Turing Machine considers." <<std::endl;
            std::cout << "-i" << ", " << "--iterations" << "\t " << "Number of iterations the Turing Machine makes in the tape."<<std::endl;
            std::cout << "-k" << ", " << "--context" << "\t" << "k indexes to consider as a context to fill the Markov Table." <<std::endl<<std::endl;

            std::cout << "Other Optional Arguments:" << std::endl;
            std::cout << "-v" << ", " << "--version" << "\t" << "Outputs the version of the program." <<std::endl;
            std::cout << "-h" << ", " << "--help" << "\t" << "Describes program." <<std::endl<<std::endl;
            
            std::cout << "Examples:" << std::endl;
            std::cout << "./tm -s 2 -a 2 -i 10 -k 1 -t .5" << std::endl;
            std::cout << "./tm --brief -s 2 -a 2 -i 10 -k 1" << std::endl;
            std::cout << "./tm --verbose --number_states=2 --alphabet_size=2 --iterations=20 --context=2" << std::endl;

            exit (0);

        case 'v':
                    std::cout << "Relative Turing Machine Version 0.1" << std::endl<<std::endl;
                    exit (0);
        case 's':
            {
            correctInput = strtol(optarg, &end, 10);
            if (*end != '\0') {
            std::cerr << "invalid input for -s/--number_states.\n";
            exit(0);
            }
            else if (correctInput<=0){
            fprintf (stderr, "-s/--number_states value was set to %d, must be an int larger than 0.\n",correctInput); 
            exit(0);
            }
            else argument.states = correctInput;
            break;
            }

        case 'a':
            {
            correctInput = strtol(optarg, &end, 10);
            if (*end != '\0') {
            std::cerr << "invalid input for -a/--alphabet_size.\n";
            exit(0);
            }
            else if (correctInput<=0){
            fprintf (stderr, "-a/--alphabet_size value was set to %d, must be an int larger than 0.\n",correctInput); 
            exit(0);
            }
            else argument.alphabet_size = correctInput;
            break;
            }

        case 'i':
            {
            correctInput = strtol(optarg, &end, 10);
            if (*end != '\0') {
            std::cerr << "invalid input for -i/--iterations.\n";
            exit(0);
            }
            else if (correctInput<=0){
            fprintf (stderr, "-i/--iterations value was set to %d, must be an int larger than 0.\n",correctInput); 
            exit(0);
            }
            else argument.numIt = correctInput;
            break;
        }
        case 'k':
        {
            correctInput = strtol(optarg, &end, 10);
            if (*end != '\0') {
            std::cerr << "invalid input for -k/--context.\n";
            exit(0);
            }
            else if (correctInput<=0){
            fprintf (stderr, "-k/--context value was set to %d, must be an int larger than 0.\n",correctInput); 
            exit(0);
            }
            else argument.k = correctInput;
            break;
        }
        case '?':
            break;

        default:
            abort ();
        }
    }

    if (verbose_flag)
        std::cerr << "verbose flag is set" << std::endl;

    if (optind < argc)
    {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
        printf ("%s ", argv[optind++]);
        putchar ('\n');
    }

    if (argument.states==0 || argument.alphabet_size==0 || argument.numIt==0 || argument.k==0 )
    {
    std::cerr << "Please fill all the required arguments" <<std::endl;
    exit(0);
    }

    printf ("states = %zu, alphabet_size = %zu, number of iterations = %u , k = %d\n",
    argument.states, argument.alphabet_size, argument.numIt, argument.k);

    if(ipow(argument.alphabet_size,argument.k) >= ipow(2,28))
    {
        fprintf (stderr, "k/context (%d) and Alphabet size/a (%zu) is too large..\n", argument.k, argument.alphabet_size);
        fprintf (stderr, " please consider a size of a^k (%zu^%d) smaller than 2^28..\n", argument.alphabet_size,argument.k);
        exit(0);
    }

    return argument;
}