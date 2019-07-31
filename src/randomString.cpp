#include "randomString.h"
#include "util.h"
#include "NormalizedCompressionMarkovTable.h"

std::vector<unsigned int> mutate_vector(double mutationRate, std::vector<unsigned int>& input_vector, unsigned int cardinality_value){
  //unsigned int randomValue;

  std::vector<unsigned int> mutated_vector(input_vector);
  srand (time(NULL));
  std::vector<unsigned int> cardinality_vector(cardinality_value);

  std::iota(cardinality_vector.begin(), cardinality_vector.end(), 0);

  for (auto it = mutated_vector.begin(); it !=  mutated_vector.end(); ++it){  
    
    if(rand() / (RAND_MAX + 1.0) < mutationRate){
      //while((randomValue = cardinality_vector[rand() % cardinality_value]) == *it )
      //;
      *it = cardinality_vector[rand() % cardinality_value];
      continue;
    }

  }  
  return mutated_vector;
}

template <typename M>
Metrics string_metrics(const std::vector<unsigned int>& mutated_vector, M& compressionTable) {

    Metrics metrics = compressionTable.update_string(mutated_vector);
    compressionTable.reset();
  return metrics;
}

void nc_mutated_string(size_t alphabet_size){
  
  std::vector<unsigned int> input_vector(10000,0);
  std::cerr << "Performing NC calculation of input String" << std::endl;
  
  std::vector <unsigned int> kvector(8);
  std::generate(kvector.begin(), kvector.end(),[n = 2] () mutable { return n++; });
  
  BestKMarkovTables<NormalizedCompressionMarkovTable> bestMkvTableCompression(kvector, alphabet_size);
  std::vector<unsigned int> mutated_vector;
  std::cout << "mutation Rate" << "\t" << "amplitude" << "\t" << "k" << "\t" << "nc" << "\t" << "sc" << std::endl;
  for (unsigned int i=0; i<=100; ++i){
    double mutationRate = static_cast<double>(i)/100;
    mutated_vector = mutate_vector(mutationRate,input_vector,alphabet_size);

    auto metrics = string_metrics(mutated_vector, bestMkvTableCompression);
    
    std::cout << i << "\t" << metrics.amplitude << "\t" << metrics.k << "\t"
    << metrics.amplitude << "\t"<< metrics.normalizedCompression << "\t" << metrics.selfCompression << std::endl;
  } 
}
