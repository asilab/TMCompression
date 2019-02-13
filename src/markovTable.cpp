/**
    markovTable.cpp
    Purpose: Create and Fill Markov Tables.

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/
#include <math.h>

#include "markovTable.h"

/**
    Returns int base raised to the power of an int exponent.

    @param base. int of the base.
    @param exp. int of the exponent.
    @return int base raised to the power of an int exponent.
*/
size_t ipow(size_t base, size_t exp)
{
    if (exp == 0) {
      return 1;
    }
    if (exp == 1) {
      return base;
    }
    int result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }
    return result;
}

/**MarkovTable Struct*/

/**
    MarkovTable Struct. Table of repetitions a given contex has for a given alphabeth.
    Example:
    k/context=2, alphabeth size=2,  string = -010110011-

    __|_0_|_1_
    00| 0 | 1
    01| 1 | 2
    10| 1 | 1
    11| 1 | 0

    Note: All this is mapped into a vector of integers.
    @param k. Size of context to consider on the MarkovTable.
    @param alphabeth_size. Size of the alphabeth being considered by the tm.
*/
MarkovTable::MarkovTable(unsigned int k, unsigned int alphabeth_size):
  markovVector(alphabeth_size* ipow(alphabeth_size,k),0), alphSz(alphabeth_size), k(k){}

/**
    Acesses position on Markov Table, by providing a pointer to a position on array of chars.

    @param void.
    @return void.
*/
int& MarkovTable::at(const Char* characters){
    // std::cout<< "str_to_index(characters) -> " << str_to_index(characters) << std::endl;
    // std::cout<< "characters[k] -> " << characters[k]  << std::endl;
    return this->markovVector.at(( (str_to_index(characters) +1) * alphSz ) - (alphSz - characters[k]) ); 
}

std::vector<unsigned int> MarkovTable::getLine(const Char* characters){
    // std::cout<< "characters -> "<< *characters << std::endl;
    // std::cout<< "str_to_index(characters) -> " << str_to_index(characters) << std::endl;
    // std::cout<<"Begin --> " <<(((str_to_index(characters) + 1) * this->alphSz) - this->alphSz)<< std::endl;
    // std::cout<<"End --> " << (    (str_to_index(characters) + 1) * this->alphSz   ) << std::endl;

    auto it_begin = this->markovVector.begin() + (  (   (str_to_index(characters) + 1) * this->alphSz   ) - this->alphSz    );
    auto it_end = this->markovVector.begin() + (    (str_to_index(characters) + 1) * this->alphSz   );
    std::vector <unsigned int> newVec(it_begin,it_end);

    return newVec;
}




/**
    Resets Markov Table.

    @param void.
    @return void.
*/
void MarkovTable::reset() {
    std::fill(this->markovVector.begin(), this->markovVector.end(), 0);
}


/**
    Takes in pointer to char array and returns the context number on the Markov Table.

    @param const Char*. Pointer to char array.
    @return size_t. Returns context number on the Markov Table.
*/
size_t MarkovTable::str_to_index(const Char* x) {
    size_t o = 0;
    for (auto i = 0u; i < this->k; ++i) { //-1
        o = (o * this->alphSz) + x[i];
    }
    return o;
}

/**
    Prints Markov Table.

    @param void.
    @return void.
*/
void MarkovTable::print() const{
    unsigned int vector_size = this->markovVector.size();
    int counter = 0;
    std::cout << std::endl;
    std::cout << "Markov Table" << std::endl;
    for(auto&& x: this->markovVector){
        std::cout << x  << "\t";
        if(++counter == this->alphSz){
            std::cout << std::endl;
            counter = 0;
        }
    }
    std::cout << std::endl;
}

/**FillMarkovTable Struct*/
/**
    FillMarkovTable Struct. Used to interact with the tape and the MarkovTable Structs.

    @param k. Size of context to consider on the MarkovTable.
    @param alphabeth_size. Size of the alphabeth being considered by the tm.
*/
FillMarkovTable::FillMarkovTable(unsigned int k, unsigned int alphabeth_size):
mrkvTable(k, alphabeth_size),isfilled(false) {}

/**
    Fills Markov Table. It interacts directly with the table and controls the its filling.
    Reads tape which on the space which was written by the Turing machine and using that info fills the MarkovTable.

    @param tape. Tape object of the Turing Machine.
    @return void.
*/
void FillMarkovTable::fill(Tape tape){

    this->mrkvTable.reset(); // here is a reset to the mkv table

    auto b = begin(tape.tape) + tape.ind_left + 1;    
    auto e = begin(tape.tape) + tape.ind_right - mrkvTable.k;
    // std::cout << "tape.ind_left + 1 = " <<tape.ind_left + 1 << std::endl <<"tape.ind_right - mrkvTable.k = " << tape.ind_right - mrkvTable.k << std::endl;
    for (auto it = b; it != e; ++it) {
        //std::cout << *it << " ";  
        mrkvTable.at(&*it) += 1;

    }
     //this->mrkvTable.print();
    // std::cout << std::endl <<"------FILL------" << std::endl;    
}

/**
    Updates Markov Table. It interacts directly with the table and controls the its filling.
    First if the tape has more that 10 elements filled by the turing machine it uses the fill function to read all those instances and fill the 
    Markov Table. Afterwards at each iteration it uses the it_update_table function to update the table.

    @param previous_value . int of the previous value on the tape.
    @param tape. Tape object of the Turing Machine.
    @return void.
*/
void FillMarkovTable::update_table(TapeMoves tpMv, Tape tape){
 
    // std::cout << tape.ind_right - tape.ind_left << " , ";
    // auto b = begin(this->mrkvTable.markovVector);
    // auto e = end(this->mrkvTable.markovVector);  
    // for (auto it = b; it != e; ++it) {
    //    if (*it<0){
    //         this->mrkvTable.print();//
    //         std::cout << tape << std::endl;//
    //         exit(1);
    //    }
    // }
     //std::cout << "moveRight = " << tpMv.moveRight << std::endl;
     //std::cout << "moveLeft = " << tpMv.moveLeft << std::endl;
     auto diff_indexes = tape.ind_right - tape.ind_left;
     // std::cout  <<"diff_indexes --> "<< diff_indexes << std::endl ;
    if ((diff_indexes) <= 3) {
        this->isfilled=false;}
    /*
    std::cout << std::endl <<"TAPE --> " ;
    
    for (auto i = tape.tape.begin() + tape.ind_left + 1 ; i != tape.tape.begin()+ tape.ind_right; ++i){
        std::cout << *i << ' ';
    }
    
    std::cout << std::endl;
    */
    if( (diff_indexes > 10) && (diff_indexes > (mrkvTable.k +2)  )  ){

        if (!this->isfilled ) {
            fill(tape);
            this->isfilled = true;
            //this->mrkvTable.print();

        }
        else{
            it_update_table(tpMv,tape);
        }
    }
}

/**
    Updates Markov Table at each iteration. It does it by adding at the table +1 in the context of the turing machine action on the table,
    and removig -1 in the context that existed previously in the tape. 

    @param previous_value . int of the previous value on the tape.
    @param tape. Tape object of the Turing Machine.
    @return void.
*/
void FillMarkovTable::it_update_table(TapeMoves tpMv, Tape tape) {
    size_t position = tape.getposition(); 
    // std::cout << "previousValue = " << tpMv.previousValue << std::endl;
    
    //std::cout << std::endl;
    // std::cout << "tape.ind_right" << tape.ind_right << std::endl;
    // std::cout << "tape.ind_left" << tape.ind_left << std::endl;
    // std::cout << "position = " << position << std::endl;

    if(tpMv.moveRight){
        auto elem = tape.tape.begin() + position - (mrkvTable.k);
        this->mrkvTable.at(&*elem)+=1;
    }

    else if(tpMv.moveLeft){
        auto elem = tape.tape.begin() + position;      
        this->mrkvTable.at(&*elem)+=1;
    }

    else {
        int actual_value = tape.tape[position];
        /*std::cout << "edition :D" << std::endl << "position = " << position << std::endl <<  "val[position] = " << tape.tape[position] << std::endl;
        std::cout << std::endl <<"TAPE --> " ;
        for (auto i = tape.tape.begin() + tape.ind_left + 1 ; i != tape.tape.begin()+ tape.ind_right; ++i){
            std::cout << *i << ' ';
        }
        std::cout << std::endl;
        */
        auto first_k = tape.tape.begin() + position - (mrkvTable.k);
        // std::cout << "first_k = " <<  position - (mrkvTable.k) << std::endl;
        

        auto first_left = tape.tape.begin() + tape.ind_left + 1;
        auto last_right = tape.tape.begin() + tape.ind_right -1;
        // std::cout << "first_left = " <<  tape.ind_left + 1 << std::endl << "last_right = " << tape.ind_right -1 << std::endl;

        auto k_it = tape.tape.begin() + position + 1;
        
        
        size_t difference_to_left_edge = position-tape.ind_left;
        size_t difference_to_right_edge =tape.ind_right - position;

        if(     (difference_to_left_edge > mrkvTable.k)    &&     (difference_to_right_edge > mrkvTable.k )   ) {  
            
            std::cout << "Hipotese 1" << std::endl;
            //mrkvTable.print();
            for (auto it = first_k; it != k_it; ++it) {
                mrkvTable.at(&*it)+=1;
                //std::cout << *it << " ";
            }
            //std::cout << std::endl;

            tape.tape[position] = tpMv.previousValue; 

            for (auto it = first_k; it != k_it; ++it) {
                mrkvTable.at(&*it)-=1;
                //std::cout << *it << " ";
            }            

            tape.tape[position] = actual_value;

        }

        else if(    (difference_to_left_edge <= mrkvTable.k)    &&    (difference_to_right_edge > mrkvTable.k )  ){
            // std::cout << "Hipotese 2" << std::endl; //PARECE ESTAR A FUNCIONAR

            for (auto it = first_left; it != k_it; ++it) {
                mrkvTable.at(&*it)+=1;
               // std::cout << *it << " ";
            }
            //std::cout <<  std::endl;

            tape.tape[position] = tpMv.previousValue; 
            
            for (auto it = first_left; it != k_it; ++it) {
                mrkvTable.at(&*it)-=1;
                // std::cout << *it << " ";
            }
            //std::cout <<  std::endl;

            tape.tape[position] = actual_value;

        }
        
        else if(    (difference_to_left_edge > mrkvTable.k)    &&     (difference_to_right_edge <= mrkvTable.k )   ){
            //std::cout << "Hipotese 3" << std::endl;

            for (auto it = first_k; it != (last_right + 1 - mrkvTable.k); ++it) {
                mrkvTable.at(&*it)+=1;
            }
            
            tape.tape[position] = tpMv.previousValue; 

            for (auto it = first_k; it != (last_right + 1 - mrkvTable.k); ++it) {
                mrkvTable.at(&*it)-=1;
            }
            tape.tape[position] = actual_value;

        }

        else if(    (difference_to_left_edge <= mrkvTable.k)    &&     (difference_to_right_edge <= mrkvTable.k )   ){
            std::cout << "Hipotese 4" << std::endl;


            for (auto it = first_left; it != (last_right + 1 - mrkvTable.k); ++it) {
                mrkvTable.at(&*it)+=1;
                //std::cout << *it << " ";
            }
            std::cout <<  std::endl;

            tape.tape[position] = tpMv.previousValue; 

            for (auto it = first_left; it != (last_right + 1 - mrkvTable.k); ++it) {
                mrkvTable.at(&*it)-=1;
                //std::cout << *it << " ";
            }
            std::cout <<  std::endl;
            tape.tape[position] = actual_value;
            std::cout << "GONNA BREAK";
            exit(0);

        }
        else{

            std::cout << "WTF GONNA BREAK";
            exit(0);
        }
        
    }
    //this->mrkvTable.print();
}

/*------------------------------------------------*/
/*------------------------------------------------*/
/*------------------------------------------------*/

NormalizedCompressionMarkovTable::NormalizedCompressionMarkovTable(unsigned int k, unsigned int alphabeth_size):
mrkvTable(k, alphabeth_size),isfilled(false) {}

double NormalizedCompressionMarkovTable::update_nc_mk_table(Tape tape){
    auto b = begin(tape.tape) + tape.ind_left- mrkvTable.k  + 1 ; // To have k context at the begining    
    auto e = begin(tape.tape) + tape.ind_right - mrkvTable.k;
    

    int diff_indexes = (tape.ind_right) - (tape.ind_left + 1);
    unsigned int value = 0 ;

        for (auto it = b; it != e; ++it) {
            auto indxvalue = this->mrkvTable.at(&*it) + 1;
            auto subvectorOfMarkovTable = this->mrkvTable.getLine(&*it); 
            
            std::transform(subvectorOfMarkovTable.begin(), subvectorOfMarkovTable.end(), subvectorOfMarkovTable.begin(), bind2nd(std::plus<int>(), 1)); 
            auto logaritm = calculateLog(indxvalue    ,   sum_all_elements_vector(subvectorOfMarkovTable));
            value += logaritm;
            this->mrkvTable.at(&*it)+=1;
    }
    return (value/normalization_base(diff_indexes, this->mrkvTable.alphSz));
}

/**
    Calculates the normalization_base by multiplying the number of elements in the input times the log_2 of the cardinality of the alphabet;
       
    @param std::vector<unsigned int>& subvector_markovtable. The reference to a sub vector of the input.
    @return void.
*/
double NormalizedCompressionMarkovTable::normalization_base(unsigned int length_of_tape, unsigned int cardinality){
   if (cardinality<0)
    {
        std::cerr << "Cardinality of string error " << std::endl;
        exit(0);
    }

   return ( length_of_tape * log2(cardinality) ); 
}

/**
    Sums all elements of the input vector;
       
    @param std::vector<unsigned int>& subvector_markovtable. The reference to a sub vector of the MarkovTable.
    @return int. sum of all vector elements
*/
int NormalizedCompressionMarkovTable::sum_all_elements_vector(std::vector<unsigned int>& subvector_markovtable)
{
    int sum_of_elems = 0;

    for (auto& n : subvector_markovtable){
        sum_of_elems += n;
        }
    
    // std::cout << "sum_all_line_elem = " << sum_of_elems << std::endl ;
    return sum_of_elems;
}

/**
    calculates the Logarithm of the ratio between two ints and returns a double;
    
    @param std::vector<unsigned int>& subvector_markovtable. The reference to a sub vector of the MarkovTable.
    @return double. Minus the log2 of the (index_value/sum_all_line_elem)/normalizer.
*/
double NormalizedCompressionMarkovTable::calculateLog(int index_value, int sum_all_line_elem){
    
    auto value = static_cast<double>(index_value)/ static_cast<double>(sum_all_line_elem);
    // std::cout << "value div = " << value << std::endl ;
    return (- log2(value));
}