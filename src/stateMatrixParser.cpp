#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "NormalizedCompressionMarkovTable.h"
#include "stateMatrixParser.h"



std::vector<Metrics> mutate_state_matrix(const std::string & state_matrix_string,unsigned int states, unsigned int  alphabet_size,unsigned int numIt, bool print ){
    StateMatrix stM = string_to_state_matrix(state_matrix_string,states,alphabet_size);
    std::vector<unsigned int> kvector{2,3,4,5,6,7,8,9};
    BestKMarkovTables<NormalizedCompressionMarkovTable> bestMkvTableCompression(kvector, alphabet_size);
    std::vector<Metrics> m_vector;
    for (auto index = 0u; index<stM.get_size(); index++){
        Metrics metrics;
        bestMkvTableCompression.reset();
        TuringRecord tr{0,0,0};
        std::vector<unsigned int> block_nc;
        auto a = stM.get_element(index);

        stM.v[index] = tr;
        auto vector_written_string = recreate_tm(stM, states, alphabet_size, numIt);
        block_nc.insert(block_nc.end(), vector_written_string.begin(), vector_written_string.end());
        
        while(tr.next(10,2)){
            stM.v[index] = tr;
            auto vector_written_string = recreate_tm(stM, states, alphabet_size, numIt);
            block_nc.insert(block_nc.end(), vector_written_string.begin(), vector_written_string.end());
        }
        
        //compute best NC

        metrics = bestMkvTableCompression.update_string(block_nc);
        if(print){
          std::cout << "--------------------------------------" << std::endl;
          std::cout << "Rule :" << index +1 << std::endl;
          std::cout << "best k:" <<metrics.k << std::endl;
          std::cout << "amplitude:" << metrics.amplitude << std::endl;
          std::cout << "normalizedCompression:" << metrics.normalizedCompression << std::endl;
          std::cout << "--------------------------------------" << std::endl;
        }
        m_vector.push_back(metrics);
        stM.v[index]=a;
    }
    return m_vector;
}

std::vector<Metrics> permutate_state_matrix(const std::string& state_matrix_string,unsigned int states, unsigned int  alphabet_size,unsigned int numIt, bool print ){
  StateMatrix stM = string_to_state_matrix(state_matrix_string,states,alphabet_size);
  std::vector<unsigned int> kvector{2,3,4,5,6,7,8,9};
  BestKMarkovTables<NormalizedCompressionMarkovTable> bestMkvTableCompression(kvector, alphabet_size);
  std::vector<Metrics> m_vector;
  StateMatrix state_matrix(states,alphabet_size);
  Metrics metrics;

  for (auto index=0u;index<1000; index++){
    auto rule_matrix_vector=stM.get_vector();
    std::random_shuffle(rule_matrix_vector.begin(),rule_matrix_vector.end() );
    state_matrix.v=rule_matrix_vector;
    auto vector_written_string = recreate_tm(state_matrix, states, alphabet_size, numIt);
    metrics = bestMkvTableCompression.update_string(vector_written_string);
    
    if(print){
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Rule :" << index +1 << std::endl;
        std::cout << "best k:" <<metrics.k << std::endl;
        std::cout << "amplitude:" << metrics.amplitude << std::endl;
        std::cout << "normalizedCompression:" << metrics.normalizedCompression << std::endl;
        std::cout << "--------------------------------------" << std::endl;
    }
    m_vector.push_back(metrics);
  }

  return m_vector;
          

}
      
void evolve_tm(unsigned int number_of_tms, unsigned int states, unsigned int alphabet_size){
    std::random_device rnd_device;
    Rng rng{rnd_device()};
    
    std::vector<unsigned int> kvector{2,3,4,5,6,7,8,9};    
    unsigned int number_iterations = 5000;
    BestKMarkovTables<NormalizedCompressionMarkovTable> bestMkvTableCompression(kvector, alphabet_size);
    Metrics ncValue_initial;
    Metrics ncValue_final;

    unsigned int amplitude_criteria = 50;

    StateMatrix stMatrix(states, alphabet_size);
    StateMatrix stMatrix2(states, alphabet_size);   
    stMatrix.set_random(rng);
    while(! machine_filter(stMatrix, states, alphabet_size, number_iterations, amplitude_criteria,bestMkvTableCompression) ){
         stMatrix.set_random(rng);
    }
    auto written = recreate_tm(stMatrix, states, alphabet_size, number_iterations);
    ncValue_initial = bestMkvTableCompression.update_string(written);
    
    auto stMatrix_pair = mutate_rules_once_at_a_time(stMatrix, states, alphabet_size, number_iterations, bestMkvTableCompression);

    for (auto counter = 0ull; counter < number_of_tms - 1; counter++) {
      stMatrix2.set_random(rng);
      while(! machine_filter(stMatrix2, states, alphabet_size, number_iterations, amplitude_criteria, bestMkvTableCompression) ){
         stMatrix2.set_random(rng);
      }

      auto stMatrix2_pair = mutate_rules_once_at_a_time(stMatrix2, states, alphabet_size, number_iterations,bestMkvTableCompression);
      
      stMatrix = artificial_selection(stMatrix_pair, stMatrix2_pair);

      stMatrix_pair = mutate_rules_once_at_a_time(stMatrix, states, alphabet_size, number_iterations,bestMkvTableCompression);
    }

    written = recreate_tm(stMatrix_pair.second, states, alphabet_size, number_iterations);
    ncValue_final = bestMkvTableCompression.update_string(written);
    std::cout << ncValue_initial.amplitude << "\t" << ncValue_initial.selfCompression << "\t" << ncValue_initial.normalizedCompression << "\t" << 
    ncValue_final.amplitude << "\t" << ncValue_final.selfCompression << "\t" << ncValue_final.normalizedCompression << std::endl;
    bestMkvTableCompression.reset();
}

void evolve_multiple_tms(unsigned int repeats , unsigned int number_of_tms,unsigned int states,unsigned int alphabet_size){
  std::cout << "amp_ini" << "\t" << "SC_ini" << "\t" << "NC_ini" << "\t" << "amp_fin" << "\t" << "SC_fin" << "\t" << "NC_fin" << std::endl;
  
  for (auto i = 0u; i<repeats;++i){
    evolve_tm(number_of_tms, states,alphabet_size);
  }
}

void evolve_multiple_tms2(unsigned int repeats , unsigned int number_of_iterations,unsigned int states,unsigned int alphabet_size){
  std::cout << "amp_ini" << "\t" << "SC_ini" << "\t" << "NC_ini" << "\t" << "amp_fin" << "\t" << "SC_fin" << "\t" << "NC_fin" << std::endl;
  unsigned int number_of_tm_improves = 1000;
  for (auto i = 0u; i<repeats;++i){
    real_nc_evolution(number_of_tm_improves, number_of_iterations, states, alphabet_size, true);
  }
}

void evolve_multiple_tms_graph(unsigned int max_number_tm_improve_repeats , unsigned int max_number_tm_tape_iterations,unsigned int states,unsigned int alphabet_size){
  std::cout << "repeats" << "\t" << "tape It" << "\t" << "Avg_Amp" << "\t" << "Avg_SC" << "\t" << "Avg_NC_variation" << std::endl;
  unsigned int number_tms=2000;
  for (auto repeats = 50u; repeats<=max_number_tm_improve_repeats;repeats=repeats*2){
    for (auto tm_tape_it = 500u; tm_tape_it<=max_number_tm_tape_iterations;tm_tape_it=tm_tape_it*2){
      Metrics avg_metrics = avg_real_tm_nc_evolution(number_tms, repeats, tm_tape_it, states, alphabet_size);
      std::cout << repeats << "\t" << tm_tape_it << "\t" << avg_metrics.amplitude << "\t" << avg_metrics.selfCompression << "\t" << avg_metrics.normalizedCompression << std::endl;
    }
  }
}


Metrics avg_real_tm_nc_evolution(unsigned int number_tms, unsigned int tm_improve_repeats , unsigned int tm_tape_iterations,unsigned int states,unsigned int alphabet_size){
  std::vector<Metrics> vector_metrics;//also amplitude---
  for (auto i = 0u; i<number_tms;++i){
    vector_metrics.push_back(real_nc_evolution(tm_improve_repeats, tm_tape_iterations, states,alphabet_size, false));
  }
return avg_metrics(vector_metrics);
}



StateMatrix artificial_selection(std::pair<std::vector<double>,StateMatrix> state_matrix_pair_1, std::pair<std::vector<double>,StateMatrix> state_matrix_pair_2){
   
  
  for(auto index=0u;index<state_matrix_pair_1.first.size();++index){
    double absolute_value = std::abs(state_matrix_pair_1.first[index]-state_matrix_pair_2.first[index]);
    
    if (absolute_value>=0.1){
      if (state_matrix_pair_2.first[index]>state_matrix_pair_1.first[index] && state_matrix_pair_2.first[index]>0){
        
        TuringRecord tr = state_matrix_pair_2.second.get_element(index);
        state_matrix_pair_1.second.set_rule(index, tr);
      }
    }
  }
  return state_matrix_pair_1.second;
}

Metrics real_nc_evolution(unsigned int number_tm_it,unsigned int tm_tape_iterations, unsigned int states, unsigned int alphabet_size, bool print){

  std::random_device rnd_device;
  unsigned int seed =rnd_device();
  Rng rng{seed};
  //std::cerr << seed << std::endl;
  std::vector<unsigned int> kvector{2,3,4,5,6,7,8,9};    
  unsigned int amplitude_criteria = 50;//parameter
  Metrics values_initial;
  Metrics values_final;
  BestKMarkovTables<NormalizedCompressionMarkovTable> bestMkvTableCompression(kvector, alphabet_size);
  StateMatrix stMatrix(states, alphabet_size);
  stMatrix.set_random(rng);
  while(! machine_filter(stMatrix, states, alphabet_size, tm_tape_iterations, amplitude_criteria,bestMkvTableCompression) ){
        stMatrix.set_random(rng);
  }
  auto vector_written_string = recreate_tm(stMatrix, states, alphabet_size, tm_tape_iterations);
  values_initial = bestMkvTableCompression.update_string(vector_written_string);
  auto amplitude = values_initial.amplitude;
  auto nc = values_initial.normalizedCompression;
  bestMkvTableCompression.reset();

  auto rules = uniform_int_distribution<unsigned int>(0, (alphabet_size * states)- 1);
  for (auto counter = 0u; counter < number_tm_it; ++counter){
    unsigned int rule_index = rules(rng);
    auto tr_original = stMatrix.get_element(rule_index);
    auto tr_random = set_random(rng, states, alphabet_size);
    while(tr_original==tr_random){
      Rng rng2{rnd_device()};
      tr_random = set_random(rng2, states, alphabet_size);
    }
    stMatrix.set_rule(rule_index, tr_random);
    vector_written_string = recreate_tm(stMatrix, states, alphabet_size, tm_tape_iterations);
    Metrics results = bestMkvTableCompression.update_string(vector_written_string);
    bestMkvTableCompression.reset();
    auto amplitude2 = results.amplitude;
    auto nc2 = results.normalizedCompression;
    if ( (nc2 <= nc) || (amplitude2*2 < amplitude || amplitude2 < 100) ){
      stMatrix.set_rule(rule_index, tr_original);
    }
    else{
      nc = nc2;
      amplitude = amplitude2;
    }
  }
  vector_written_string = recreate_tm(stMatrix, states, alphabet_size, tm_tape_iterations);
  values_final = bestMkvTableCompression.update_string(vector_written_string);
  bestMkvTableCompression.reset();
  if (print){
  std::cout << values_initial.amplitude << "\t" << values_initial.selfCompression << "\t" << values_initial.normalizedCompression << "\t" << 
  values_final.amplitude << "\t" << values_final.selfCompression << "\t" << values_final.normalizedCompression << std::endl; 
  }
  Metrics variation;
  variation.amplitude = values_final.amplitude;
  variation.normalizedCompression = (values_final.normalizedCompression - values_initial.normalizedCompression);
  variation.selfCompression = (values_final.selfCompression - values_initial.selfCompression);
  
  return variation;
//the algorithm:
// 1)Create random tm;
// 2)Randomly select rule index;
// 3)Permute randomly rule;
// 4)Compute NC and Amplitude;
// 5) if it does not improve NC higher and Amplitude higher than 100 chars, permute rule;
// 6)it improves, yes change rule repeat 2-4 until numb_tm_it;
// 7) print tape and state matrix;
}


StateMatrix string_to_state_matrix(std::string string_state_matrix, unsigned int number_of_states, unsigned int alphabet_size){
    if(!(is_string_char_number(string_state_matrix) && (string_state_matrix.size()%(3*number_of_states*alphabet_size)==0) )){
      fprintf (stderr,"Invalid input string of TM State Matrix : %s\n ", string_state_matrix.c_str());
      exit(0);
    }
 
  //std::cout << "string state matrix : " << string_state_matrix << std::endl;
  return splitString(string_state_matrix,3, number_of_states, alphabet_size);
}

StateMatrix splitString(const std::string& str, int splitLength, unsigned int number_of_states, unsigned int alphabet_size){
   
   int NumSubstrings = str.length() / splitLength;
   std::vector<TuringRecord> ret;
   StateMatrix st(number_of_states, alphabet_size);


   for (auto i = 0; i < NumSubstrings; i++)
   {
        std::string tuple = str.substr(i * splitLength, splitLength);
        unsigned int w = tuple[0] - '0';
        unsigned int m = tuple[1] - '0';
        unsigned int s = tuple[2] - '0';
        bool test = (w < alphabet_size) && (m<3) && (s<number_of_states);
        if (!test){
            std::cout << alphabet_size << " , " << number_of_states <<std::endl;
            fprintf (stderr,"Invalid input string of TM State Matrix in tuple : %s\n ", tuple.c_str());
            exit(0);
        }
        //std::cout << w << m << s << std::endl;
        ret.push_back(TuringRecord{w,m,s});
   }
    for (auto i=0u; i<st.v.size(); i++){
      st.v[i] = ret[i];
    }
    //print(ret);
   return st;
}

bool is_string_char_number(const std::string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

std::vector<unsigned int> recreate_tm(StateMatrix stM, unsigned int states, unsigned int  alphabet_size, unsigned int numIt){

  TuringMachine machine(states, alphabet_size);    
  machine.set_state_matrix(stM); 
  machine.reset_tape_and_state();
  
  for (auto i = 0u; i < numIt -1 ; ++i){
    machine.act();
  }

  return machine.get_written_tape();
}

std::pair<std::vector<unsigned int>,StateMatrix> random_tm(Rng rng, unsigned int states, unsigned int  alphabet_size, unsigned int numIt){
  TuringMachine machine(states, alphabet_size);    
  machine.stMatrix.set_random(rng);
  machine.reset_tape_and_state();
  
  for (auto i = 0u; i < numIt -1 ; ++i){
    machine.act();
  }
  std::pair<std::vector<unsigned int>,StateMatrix> pair_tape_state_matrix(machine.get_written_tape(),machine.get_state_matrix());
  return pair_tape_state_matrix;
}

std::pair<std::vector<double>,StateMatrix> mutate_rules_once_at_a_time(StateMatrix stM, unsigned int states, unsigned int  alphabet_size, unsigned int numIt,BestKMarkovTables<NormalizedCompressionMarkovTable>& bestMkvTableCompression){
  bool baseline = true;
  std::vector<Metrics> all_other_permutation_metrics_in_rules;
  std::vector<Metrics> all_other_permutation_metrics_avg_per_rule;
  Metrics baselineTM;
  
  for (auto index = 0u; index<stM.get_size(); index++){
    
    TuringRecord tr{0,0,0};
    TuringRecord element_tr = stM.get_element(index);
    
    if(!(tr==element_tr)){
      stM.set_rule(index,tr);
      auto vector_written_string = recreate_tm(stM, states, alphabet_size, numIt);
      all_other_permutation_metrics_in_rules.push_back(bestMkvTableCompression.update_string(vector_written_string));
      bestMkvTableCompression.reset();
    }
    else if(baseline){
      auto vector_written_string = recreate_tm(stM, states, alphabet_size, numIt);
      baselineTM = bestMkvTableCompression.update_string(vector_written_string);
      bestMkvTableCompression.reset();
      baseline = false;
    }
      
    while(tr.next(states,alphabet_size)){
      if(!(tr==element_tr)){
        stM.set_rule(index,tr);
        auto vector_written_string = recreate_tm(stM, states, alphabet_size, numIt);
        all_other_permutation_metrics_in_rules.push_back(bestMkvTableCompression.update_string(vector_written_string));
        bestMkvTableCompression.reset();
      }
      else if(baseline){
      auto vector_written_string = recreate_tm(stM, states, alphabet_size, numIt);
      baselineTM= bestMkvTableCompression.update_string(vector_written_string);
      bestMkvTableCompression.reset();
      baseline = false;
      }
    }
    all_other_permutation_metrics_avg_per_rule.push_back(avg_metrics(all_other_permutation_metrics_in_rules));
    stM.set_rule(index,element_tr);
  }
  std::vector<double> rule_relevance_vector;
  for (auto other_rules_avg:all_other_permutation_metrics_avg_per_rule){
    double rule_relevance = baselineTM.normalizedCompression - other_rules_avg.normalizedCompression;
    rule_relevance_vector.push_back(rule_relevance); 
  }
  bestMkvTableCompression.reset();
  std::pair<std::vector<double>,StateMatrix> pair_rule_relevance_stm(rule_relevance_vector,stM);
  return pair_rule_relevance_stm;
}

bool machine_filter(StateMatrix state_matrix, unsigned int states,unsigned int alphabet_size, unsigned int numIt, unsigned int amplitude_criteria,
                    BestKMarkovTables<NormalizedCompressionMarkovTable>& bestMkvTableCompression){

    
  TuringMachine machine(states, alphabet_size);    
  machine.set_state_matrix(state_matrix); 
  machine.reset_tape_and_state();

  for (auto i = 0u; i < numIt -1 ; ++i){
    machine.act();
  }
  auto amplitude = bestMkvTableCompression.update_string(machine.get_written_tape()).amplitude;
  bestMkvTableCompression.reset();
  return amplitude > amplitude_criteria;
}