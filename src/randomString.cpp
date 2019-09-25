#include <string>
#include <fstream>
#include <streambuf>
#include <map>
#include <algorithm>
#include <utility>
#include <ios>
#include <iomanip>
#include <random>

#include "randomString.h"
#include "util.h"
#include "NormalizedCompressionMarkovTable.h"

template<typename T>
std::vector<T> slice(std::vector<T> const &v, unsigned int m, unsigned int n){
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;

    std::vector<T> vec(first, last);
    return vec;
}

template<typename T>
void print(std::vector<T> const &v){
    for (auto i: v) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}
int randomfunc(unsigned int j) 
{ 
    return rand() % j; 
} 
  
template <typename M>
Metrics string_metrics(const std::vector<unsigned int>& mutated_vector, M& compressionTable) {
    compressionTable.reset();
    Metrics metrics = compressionTable.update_string(mutated_vector);
  return metrics;
}

std::pair<std::vector<unsigned int>,unsigned int>read_dna_file(std::string virus_path){
  std::ifstream t(virus_path);
  std::string str;

  t.seekg(0, std::ios::end);   
  str.reserve(t.tellg());
  t.seekg(0, std::ios::beg);

  str.assign((std::istreambuf_iterator<char>(t)),
              std::istreambuf_iterator<char>());

  str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
  str.erase(std::remove(str.begin(), str.end(), 'N'), str.end());
  
	return getinputContent(str);
}

std::pair<std::vector<unsigned int>,unsigned int> getinputContent(const std::string& str){
  
  
  std::map<char, unsigned int> mapping;
  std::pair <std::vector<unsigned int>,unsigned int> mapvector_cardinality_pair;
  if(str.size() > 0){
    int counter = -1;
    for (auto it=str.begin(); it!=str.end(); ++it){
      if ( mapping.find(*it) == mapping.end()){
        mapping[*it] = ++counter;
        mapvector_cardinality_pair.first.push_back(counter);
      }
      else{
        mapvector_cardinality_pair.first.push_back(mapping.find(*it)->second);
      }           
    }
  }

    mapvector_cardinality_pair.second = mapping.size();
  return mapvector_cardinality_pair;
}

std::vector<unsigned int> edit_vector(double mutationRate,
                                        std::vector<unsigned int>& input_vector, 
                                        unsigned int cardinality_value, 
                                        bool natural_sequence){
                                          
  std::vector<unsigned int> mutated_vector(input_vector);
  srand (time(NULL));
  std::vector<unsigned int> cardinality_vector(cardinality_value);
  std::iota(cardinality_vector.begin(), cardinality_vector.end(), 0);

  for (auto it = mutated_vector.begin(); it !=  mutated_vector.end(); ++it){  
      if(rand() / (RAND_MAX + 1.0) < mutationRate){
        if (!natural_sequence){
          *it = cardinality_vector[rand() % cardinality_value];
          continue;
        }
        else{
          *it = cardinality_vector[0];
          continue;
        }
      }
  }  
  return mutated_vector;
}

std::vector <std::vector <unsigned int>> permutate_vector(const std::vector <unsigned int>& edited_vector){
  std::vector <std::vector <unsigned int>>permutations_vector;
  unsigned int seq_size = edited_vector.size();
  double x = 0;
  unsigned int  y = 0;  

  while (y < seq_size){
    auto chunked_subvectors = divide_to_chunks_vector(edited_vector, y);
    permutations_vector.push_back(shuffle_vector(chunked_subvectors));
    y = pow(x,3.0);
    ++x;
  }
  return permutations_vector;
}

std::vector <std::vector <unsigned int>> divide_to_chunks_vector(const std::vector <unsigned int>& edited_vector, unsigned int& divisions){
    std::vector <unsigned int>copyofVector(edited_vector);
    unsigned int chunks = divisions + 1;
    unsigned int seq_size = edited_vector.size();
    unsigned int size_of_chunks = round((double)seq_size/(double)chunks); 
    std::vector <std::vector <unsigned int>>  chunked_vector((seq_size + size_of_chunks) / size_of_chunks);
    for(unsigned int i = 0; i < seq_size; i += size_of_chunks) {
      auto last = std::min(seq_size, i + size_of_chunks);
      auto index = i / size_of_chunks;
      auto& vec = chunked_vector[index];
      vec.reserve(last - i);
      std::move(copyofVector.begin() + i, copyofVector.begin() + last, std::back_inserter(vec));
    }
    
    if (chunked_vector.back().empty()){
        chunked_vector.pop_back();
    }
    
    if (chunked_vector.back().size() < size_of_chunks){
      chunked_vector.rbegin()[1].insert( chunked_vector.rbegin()[1].end(), chunked_vector.back().begin(), chunked_vector.back().end() );
      chunked_vector.pop_back();
    }


    return chunked_vector;
}

std::vector <unsigned int> shuffle_vector(const std::vector <std::vector <unsigned int>>& chunked_vector){
  
  std::vector <std::vector <unsigned int>> copy_chunked_vector(chunked_vector);
  
  std::random_shuffle(std::begin(copy_chunked_vector), std::end(copy_chunked_vector), randomfunc);
  std::vector<unsigned int>  flattenedChunk = std::accumulate(copy_chunked_vector.begin(), copy_chunked_vector.end(), std::vector<unsigned int>(),[]
  (std::vector<unsigned int> a, std::vector<unsigned int> b) 
    {a.insert(a.end(), b.begin(), b.end());
        return a;
    });
  
  return flattenedChunk;
}

void nc_substitution_permutate_sequence(bool natural_sequence, const std::string& virus_path){
  
  std::cerr << "Performing NC calculation of input String" << std::endl;

  std::pair<std::vector<unsigned int>,unsigned int> vector_and_cardinality;
  std::vector<unsigned int> mutated_vector;
  std::vector <unsigned int> kvector(8);
  std::generate(kvector.begin(), kvector.end(),[n = 2] () mutable { return n++; });
  if(natural_sequence){
    vector_and_cardinality = read_dna_file(virus_path);
  }
  else{

    std::vector<unsigned int> generated_vector(500, 0);;
    std::vector<unsigned int> vector2(500, 1);;
    generated_vector.insert( generated_vector.end(), vector2.begin(), vector2.end() );
    vector_and_cardinality.first = generated_vector;
    vector_and_cardinality.second = 2;
  }

  BestKMarkovTables<NormalizedCompressionMarkovTable> bestMkvTableCompression(kvector, vector_and_cardinality.second);
  
  for (unsigned int i=0; i<=100; ++i){
    double mutationRate = static_cast<double>(i)/100;
    auto edited_vector = edit_vector(mutationRate, vector_and_cardinality.first ,vector_and_cardinality.second, natural_sequence);
    std::vector <std::vector <unsigned int>> permutations_vector = permutate_vector(edited_vector);
    unsigned int counter = 0;
    for(unsigned int j=0; j<permutations_vector.size(); ++j){

      auto metrics = string_metrics(permutations_vector[j], bestMkvTableCompression); 
      std::cout << i << "\t" <<  pow(counter,3.0) << "\t"<< metrics.normalizedCompression << std::endl;
      counter+=1;
    }
    std::cout << std::endl;
  } 

}