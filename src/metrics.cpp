/**
    metrics.cpp
    Purpose: Mesure Behaviour of Turing Machines.

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#include "metrics.h"

    
  void CompressionResultsData::append(TmId tmNumber,
  unsigned int amplitudes,
  double self_compression,
  double normalized_compression){
    
    this->tmNumber.tmNumber.push_back(tmNumber);
    this->amplitude.push_back(amplitudes);
    this->self_compression.push_back(self_compression);
    this->normalized_compression.push_back(normalized_compression);

  }

  void CompressionResultsData::clear_data(){
    this->tmNumber.tmNumber.clear();
    this->amplitude.clear();
    this->self_compression.clear();
    this->normalized_compression.clear();
  }

  void CompressionResultsData::avg(){
    std::pair<double,double> amp;
    std::pair<double,double> sc;
    std::pair<double,double> nc;

    amp.first = std::accumulate( this->amplitude.begin(), this->amplitude.end(), 0.0)/this->amplitude.size();
    double sq_amp_sum = std::inner_product(this->amplitude.begin(), this->amplitude.end(), this->amplitude.begin(), 0.0);
    amp.second = std::sqrt(sq_amp_sum / this->amplitude.size() - amp.first * amp.first);

    sc.first = std::accumulate( this->self_compression.begin(),  this->self_compression.end(), 0.0)/ this->self_compression.size();
    double sq_sc_sum = std::inner_product(this->self_compression.begin(), this->self_compression.end(), this->self_compression.begin(), 0.0);
    sc.second = std::sqrt(sq_sc_sum / this->self_compression.size() - sc.first * sc.first);

    nc.first = std::accumulate( this->normalized_compression.begin(), this->normalized_compression.end(), 0.0)/this->normalized_compression.size();
    double sq_nc_sum = std::inner_product(this->normalized_compression.begin(), this->normalized_compression.end(), this->normalized_compression.begin(), 0.0);
    nc.second = std::sqrt(sq_nc_sum / this->normalized_compression.size() - nc.first * nc.first);
    std::cout<< "Number of TM \t Mean Amp+/-std \t Mean sc+/-std \t Mean nc+/-std" << std::endl;
    std::cout <<  this->amplitude.size() << "\t\t" << amp.first << "+/-" << amp.second 
                                              << "\t\t" << sc.first << "+/-" << sc.second 
                                              << "\t" << nc.first << "+/-" << nc.second
                                              << std::endl;
  }

