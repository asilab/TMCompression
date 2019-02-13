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
            {"alphabeth_size",  required_argument, 0, 'a'},
            {"iterations",  required_argument, 0, 'i'},
            {"context",  required_argument, 0, 'k'},
            {"threshold",  required_argument, 0, 't'},

            {NULL, 0, NULL, 0}
        };
        int option_index = 0;

        c = getopt_long (argc, argv, "s:a:i:k:t:hv",
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

            std::cout << "Manditory Arguments:" << std::endl;
            std::cout << "-s" << ", " <<"--number_states" << "\t" << "Number of States the Turing Machine has." << std::endl;
            std::cout << "-a" << ", " << "--alphabeth_size" << "\t" << "Alphabeth size the Turing Machine considers." <<std::endl;
            std::cout << "-i" << ", " << "--iterations" << "\t " << "Number of iterations the Turing Machine makes in the tape."<<std::endl;
            std::cout << "-k" << ", " << "--context" << "\t" << "k indexes to consider as a context to fill the Markov Table." <<std::endl<<std::endl;
            std::cout << "-t" << ", " << "--threshold" << "\t" << "threshold of compression" <<std::endl<<std::endl;

            std::cout << "Other Optional Arguments:" << std::endl;
            std::cout << "-v" << ", " << "--version" << "\t" << "Outputs the version of the program." <<std::endl;
            std::cout << "-h" << ", " << "--help" << "\t" << "Describes program." <<std::endl<<std::endl;
            
            std::cout << "Examples:" << std::endl;
            std::cout << "./tm -s 2 -a 2 -i 10 -k 1 -t .5" << std::endl;
            std::cout << "./tm --brief -s 2 -a 2 -i 10 -k 1 -t .5" << std::endl;
            std::cout << "./tm --verbose --number_states=2 --alphabeth_size=2 --iterations=20 --context=2 --threshold=.5" << std::endl;

            exit (0);

        case 'v':
                    std::cout << "Relative Turing Machine Version 0.1" << std::endl<<std::endl;
                    exit (0);
        case 's':
            {
            correctInput = strtol(optarg, &end, 10);
            if (*end != '\0') {
            std::cout << "invalid input for -s/--number_states.\n";
            exit(0);
            }
            else if (correctInput<=0){
            printf ("-s/--number_states value was set to %d, must be an int larger than 0.\n",correctInput); 
            exit(0);
            }
            else argument.states = correctInput;
            break;
            }

        case 'a':
            {
            correctInput = strtol(optarg, &end, 10);
            if (*end != '\0') {
            std::cout << "invalid input for -a/--alphabeth_size.\n";
            exit(0);
            }
            else if (correctInput<=0){
            printf ("-a/--alphabeth_size value was set to %d, must be an int larger than 0.\n",correctInput); 
            exit(0);
            }
            else argument.alphabeth_size = correctInput;
            break;
            }

        case 'i':
            {
            correctInput = strtol(optarg, &end, 10);
            if (*end != '\0') {
            std::cout << "invalid input for -i/--iterations.\n";
            exit(0);
            }
            else if (correctInput<=0){
            printf ("-i/--iterations value was set to %d, must be an int larger than 0.\n",correctInput); 
            exit(0);
            }
            else argument.numIt = correctInput;
            break;
        }
        case 'k':
        {
            correctInput = strtol(optarg, &end, 10);
            if (*end != '\0') {
            std::cout << "invalid input for -k/--context.\n";
            exit(0);
            }
            else if (correctInput<=0){
            printf ("-k/--context value was set to %d, must be an int larger than 0.\n",correctInput); 
            exit(0);
            }
            else argument.k = correctInput;
            break;
        }
            case 't':
        {
            double correctInput2 = strtof(optarg, &end);
            if (*end != '\0') {
            std::cout << "invalid input for -t/--threshold.\n";
            exit(0);
            }
            else if (correctInput2<0 || correctInput2>1){
            printf ("-t/--threshold value was set to %d, must be a double that belongs to the interval [0,1].\n",correctInput2); 
            exit(0);
            }
            else argument.threshold = correctInput2;
            break;
        }
        case '?':
            break;

        default:
            abort ();
        }
    }

    if (verbose_flag)
    puts ("verbose flag is set");

    if (optind < argc)
    {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
        printf ("%s ", argv[optind++]);
        putchar ('\n');
    }

    if (argument.states==0 || argument.alphabeth_size==0 || argument.numIt==0 || argument.k==0 )
    {
    std::cout << "Please fill all the required arguments" <<std::endl;
    exit(0);
    }

    printf ("states = %d, alphabeth_size = %d, number of iterations = %d , k = %d, threshold = %f\n",
    argument.states, argument.alphabeth_size, argument.numIt, argument.k, argument.threshold);

    if(ipow(argument.alphabeth_size,argument.k) >= ipow(2,28))
    {
    printf ("k/context (%d) and Alphabet size/a (%d) is too large..\n", argument.k, argument.alphabeth_size);
    printf (" please consider a size of a^k (%d^%d) smaller than 2^28..\n", argument.alphabeth_size,argument.k);
    exit(0);
    }

    return argument;
}