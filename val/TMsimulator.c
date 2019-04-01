/**
    TMsimulator.c
    Purpose in our work: Program that serves has a way of validating Turing Tapes.

    @author Dr. Hector Zenil and Dr. Fernando Soler-Toscano
    Obtained From: https://www.algorithmicdynamics.net/uploads/4/3/8/0/43802527/tm1d.zip
*/



#include <stdlib.h>  // general-purpose library
#include <stdio.h>   // read-write functionality
#include <string>  // string manipulation library
#include <ctype.h>   // character classification functions
#include <gmp.h>
#include <iostream>
#include <sstream>
#include <map>
#include <utility>

using namespace std;

typedef char symbol;   // The 'symbol' is a char (256)
enum direction {DIR_LEFT, STOP, DIR_RIGHT}; // possible directions

// struct which contains the result of a transition of the TM
struct transition_result {
  int control_state;      // new state
  symbol write_symbol;    // written symbol
  enum direction dir;     // head direction
};
typedef struct transition_result transition_result;

// the state of the TM 
struct turing_machine_state {
  int control_state;    // current state
  int head_position;    // position of the head in the tape
  int max_head_position;   // number of the most-right visited cell (>=0)
  int min_head_position;   // number of the most-left visited cell  (<=0)
  int tape_r_size;      // size of the right tape 
  int tape_l_size;      // size of the left tape
  symbol* tape_r;       // right tape (array of symbols)
  symbol* tape_l;       // left tape (array of symbols)
};
typedef struct turing_machine_state turing_machine_state;

// General data of the TM
struct turing_machine {
  int number_colors;         // number of symbols
  int number_states;         // number of states
  int halting_state;         // halting state
  int initial_control_state; // initial state
  symbol blank_symbol;       // blank symbol 
  turing_machine_state state;
  transition_result** transition_table;   // REMOVE ????
};
typedef struct turing_machine turing_machine;


void show_data(turing_machine *m){
  printf("*** Printing TM state\n");
  printf("    Current state: %d\n",m->state.control_state);
  printf("    Head position: %d (Min: %d, Max: %d)\n",
	 m->state.head_position,
	 m->state.min_head_position,
	 m->state.max_head_position);
  printf("    Tape size. Left: %d. Right: %d.\n", 
	 m->state.tape_l_size,
	 m->state.tape_r_size);
  printf("    Visited tape: ");
  int i;
  for (i=m->state.min_head_position; i<=m->state.max_head_position; i++){
    if(i<0)
      printf("%d",m->state.tape_l[-1*i]);
    else 
      printf("%d",m->state.tape_r[i]);
  }    
  printf("\n");
  symbol sym;
  if(m->state.head_position >= 0)
    sym = m->state.tape_r[m->state.head_position];
  else 
    sym = m->state.tape_l[-1*(m->state.head_position)];
  printf("    Symbol to read: %d\n",sym);
  printf("    Entry in the transition table\n");
  printf("       New state: %d\n",m->transition_table[m->state.control_state][sym].control_state);
  printf("       New symbol: %d\n",m->transition_table[m->state.control_state][sym].write_symbol);
  printf("       Movement: %d\n",m->transition_table[m->state.control_state][sym].dir);
  
}

 
/*****************************************************************************
   Executes a step in the given TM
*****************************************************************************/
int run_step(turing_machine *m){

    //show_data(m);

    int cell = m->state.head_position;      // current cell
    
    symbol s1;                             // get current symbol
    if (cell >= 0){
      s1 = m->state.tape_r[cell];
    } else {
      s1 = m->state.tape_l[(-1)*cell]; // note the use of the left tape (position 0 never used)
    }
    
    // Gets the transition to apply
    transition_result tr = m->transition_table[m->state.control_state][s1];

    // Writes new symbol
    if (cell >= 0){
      m->state.tape_r[cell] = tr.write_symbol;
    } else {
      m->state.tape_l[(-1)*cell] = tr.write_symbol;
    }

    
    // Changes the state    
    m->state.control_state = tr.control_state;  

    // Stops (without moving the head) if the halting state is reached
    if(m->state.control_state == m->halting_state)
      return 0;

     
    // Moves the head and possible extends the tape
    if(tr.dir == DIR_LEFT){    // LEFT DIRECTION
      m->state.head_position--;                              // moves the head
      if(m->state.head_position < m->state.min_head_position) // if smaller than left-most position
	m->state.min_head_position = m->state.head_position;  // decreases
      // WHEN THE NEW POSITION IS SMALLER THAN THE TAPE SIZE
      if (m->state.head_position <= -1*(m->state.tape_l_size)) {  // if the end of the tape is reached
	int i, old_tape_size = m->state.tape_l_size; 
	symbol* new_tape = (symbol*) realloc(m->state.tape_l, old_tape_size*2); // increases tape size
	if (new_tape == NULL) {    // if not enough memory
	  printf("Out of memory: expanding left tape\n");//,old_tape_size);  
	  exit(-1);                // the program finishes
	}
	m->state.tape_l = new_tape;  // sets the new tape
	m->state.tape_l_size *= 2;   // the size is duplicated
	for (i=old_tape_size; i < m->state.tape_l_size; i++) { // visits all the new cells
	  m->state.tape_l[i] = m->blank_symbol; // and fills them with blanks
	}
      }
    }
    else {  // RIGHT DIRECTION
      m->state.head_position++; // moves the head
      if(m->state.head_position > m->state.max_head_position) // greater then right-most position
	m->state.max_head_position = m->state.head_position;	
      // case that is grater than size
      if (m->state.head_position >= m->state.tape_r_size) {  // if the end of the tape is reached
	int i, old_tape_size = m->state.tape_r_size; 
	symbol* new_tape = (symbol*) realloc(m->state.tape_r, old_tape_size*2); // increases tape size
	if (new_tape == NULL) {    // if not enough memory
	  printf("Out of memory: expanding right tape");  
	  exit(-1);                // the program finishes
	}
	m->state.tape_r = new_tape;  // sets the new tape
	m->state.tape_r_size *= 2;   // the size is duplicated
	for (i=old_tape_size; i < m->state.tape_r_size; i++) { // visits all the new cells
	  m->state.tape_r[i] = m->blank_symbol; // and fills them with blanks
	}
      }
    }    
    
    return 1;
    
}


/******************************************************************
  Initialization of a Turing Machine
 ******************************************************************/

turing_machine init_turing_machine(int states, int colors, int blank, mpz_t numberTM){

  turing_machine m;
  m.number_colors = colors;
  m.number_states = states;
  m.halting_state = -1;          // Halting state
  m.initial_control_state = 0;   // 
  m.blank_symbol = blank;

  // Initial state
  m.state.control_state = m.initial_control_state;
  m.state.head_position = 0;
  m.state.max_head_position = 0;
  m.state.min_head_position = 0;
  m.state.tape_r_size = 16;
  m.state.tape_l_size = 16;     
  // Right tape
  m.state.tape_r = (symbol*) malloc(sizeof(symbol)*m.state.tape_r_size); // reserves space for the tape
  if (m.state.tape_r == NULL) {  
    printf("Out of memory: creating right tape");
    exit(-1);
  }
  int t;
  for(t=0;t<m.state.tape_r_size;t++){
    m.state.tape_r[t] = m.blank_symbol;
  }
  // Left tape
  m.state.tape_l = (symbol*) malloc(sizeof(symbol)*m.state.tape_l_size); // reserves space for the tape
  if (m.state.tape_l == NULL) {  
    printf("Out of memory: creating left tape");
    exit(-1);
  }
  for(t=0;t<m.state.tape_l_size;t++){
    m.state.tape_l[t] = m.blank_symbol;
  }

  // Creation of the transition table
  //malloc the states dimension
  m.transition_table = (transition_result**) malloc(sizeof(transition_result*) * m.number_states);  
  if (m.transition_table == NULL) {    // if not enough memory
    printf("Out of memory: creating transition table (1)");  
    exit(-1);                // the program finishes
  }
  //iterate over states
  int s;
  for(s=0;s<m.number_states;s++){
    // malloc the colors dimension
    m.transition_table[s] = (transition_result*) malloc(sizeof(transition_result) * m.number_colors);
    if (m.transition_table[s] == NULL) {    // if not enough memory
      printf("Out of memory: creating transition table (2)");  
      exit(-1);                // the program finishes
    }      
  } 
 
  
  // Filling the transition table
  int i = 0;
  int j= 0;
  mpz_t gr; // rest
  mpz_t gc; // quotient
  
  mpz_init(gr);
  mpz_init(gc);
  
  int rest;
  
  for (i=states-1; i>=0; i--) {     // the order may possibly change
    for(j=0;j<colors;j++){
      
      mpz_fdiv_qr_ui(gc, gr, numberTM, colors*((2*states)+1));
      mpz_set(numberTM, gc);
      
      rest = mpz_get_ui(gr);
      
      if(rest<colors){
	m.transition_table[i][j].control_state = m.halting_state;
	m.transition_table[i][j].write_symbol = rest;
	m.transition_table[i][j].dir = STOP;
      } else {
	rest = rest - colors;

	m.transition_table[i][j].write_symbol = (rest % colors);
	rest = rest/colors;
	
	m.transition_table[i][j].dir = ((rest % 2)==0 ? DIR_RIGHT : DIR_LEFT);
	rest = rest / 2;

	m.transition_table[i][j].control_state = (rest % states); // halting state	
	
      }
    }
  }

  mpz_clear(gr);
  mpz_clear(gc);
  
    // shows the transition table (with Hector's notation)  
  std::cout << std::endl << "Turing Machine State Matrix" << std::endl<< std::endl<< "   ";;

  for (auto jj=0u;jj< states ; jj++){
    std::cout<<"    "<< jj << "     ";
  }
  std::cout << std::endl<< "   ";
  
  for (auto jj=0u;jj< states ; jj++){
    std::cout<<"----------";
  }
  
  std::cout<< std::endl;

  for(j=0;j<colors; j++){
     std::cout << j << " " << "|" << " ";
    for (i=0; i<states; i++) { 
        std::cout << "(" <<  static_cast<int16_t> (m.transition_table[i][j].write_symbol) << "," 
        << ((m.transition_table[i][j].dir)) << "," 
        << ((m.transition_table[i][j].control_state)) << ")" <<"\t";
    }
    std::cout <<std::endl;
  }
  std::cout << std::endl << "Lines --> Alphabet Letter "<< std::endl << "Columns --> TM State "<< std::endl;
  std::cout << "(w,m,s) --> (write,move,state)" << std::endl;



  // shows the transition table (with Hector's notation)  
  /*   for (i=0; i<states; i++) { 
    for(j=colors-1;j>=0; j--){
      printf("{%i, %i} -> {%i, %i, %i}\n",
	     i+1,j,
	     1+(m.transition_table[i][j].control_state),
	     m.transition_table[i][j].write_symbol,
	     (m.transition_table[i][j].dir)-1);
    }
    }*/ 
  

  // Returns the constructed TM
  return m;

}

void delete_state(turing_machine *m){
  free(m->state.tape_r);
  free(m->state.tape_l);
  int i;
  for(i=0;i<m->number_states;i++){
    free(m->transition_table[i]);
  }
  free(m->transition_table);
}


string outputTM(turing_machine *m){
  if(m->state.control_state != m->halting_state)
    return "-1";
  string sout = "";
  char symb;
  
  int i;
  for (i=m->state.min_head_position; i<=m->state.max_head_position; i++){
    if(i<0){
      symb = (m->state.tape_l[-1*i])+'0';
    } else {
      symb = (m->state.tape_r[i])+'0';
    }
    sout = sout+symb; 
  }   
  return sout;
}


int main(int argn, char* argv[]) {
  // Arguments:
  // - <s>
  // - <k>
  // - maxRuntime
  // - initTM
  // - end TM
  
  turing_machine machine;
  
  map<string, unsigned long long> results;
  string out;
  int i;

  int s = atoi(argv[1]);
  int k = atoi(argv[2]);
  int runtime =  atoi(argv[3]);

  mpz_t TM;
  mpz_init_set_str(TM,argv[4],10);

  mpz_t Last;
  mpz_init_set_str(Last,argv[5],10);

  mpz_t acc;
  mpz_init(acc);
  //  int count = 0;

  while(mpz_cmp(TM,Last)<=0){
    mpz_set(acc,TM);
    machine = init_turing_machine(s,k,0,acc);
    for(i=0; i<runtime && run_step(&machine); i++){};
    show_data(&machine);
    out = outputTM(&machine);  
    ++results[out];
    delete_state(&machine);
    mpz_add_ui(TM,TM,1);    
    //  count++;
    //  if(count==1000000000){
    //    printf("One billion more\n");
    //   count = 0;
    // }
  }

  mpz_clear(TM);
  mpz_clear(Last);
  mpz_clear(acc);

  // Prints the results
  for( map<string,unsigned long long>::iterator ii=results.begin(); ii!=results.end(); ++ii)
    {
      cout << (*ii).first << " : " << (*ii).second << '\n';
    }  
  
}

