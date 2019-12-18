/**
    metrics.cpp
    Purpose: Mesure Behaviour of Turing Machines.

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/
#include <iomanip>
#include <cassert>

#include "metrics.h"

void Metrics::print(){
    std::cout << "amplitude = " << this->amplitude << std::endl;
    std::cout << "k = " << this->k << std::endl;
    std::cout << "normalized Compression = " << this->normalizedCompression << std::endl;
    std::cout << "Self Compression = " << this->selfCompression << std::endl;
}



Metrics avg_metrics(std::vector<Metrics> vector_metrics){
    Metrics metrics;
    unsigned int sum_k = 0;
    unsigned int sum_amplitude = 0;
    double sum_selfCompression = 0;
    double sum_normalizedCompression = 0;

    for (auto a:vector_metrics){
        sum_k+=a.k;
        sum_amplitude+=a.amplitude;
        sum_normalizedCompression+=a.normalizedCompression;
        sum_selfCompression+=a.selfCompression;
    }
    metrics.amplitude = sum_amplitude/vector_metrics.size(); //truncated unsigned int
    metrics.k = sum_k/vector_metrics.size(); //truncated unsigned int
    metrics.normalizedCompression= sum_normalizedCompression/vector_metrics.size();
    metrics.selfCompression= sum_selfCompression/vector_metrics.size();
    return metrics;
}

std::vector<Metrics> ranking(std::vector<Metrics> vector_metrics, unsigned int amplitude_criteria){
    std::sort(vector_metrics.begin(),vector_metrics.end(), [](const Metrics &x, const Metrics &y){ return (x.normalizedCompression > y.normalizedCompression);});
    vector_metrics.erase(
    std::remove_if( vector_metrics.begin(), vector_metrics.end(), [amplitude_criteria](const Metrics& x) { return x.amplitude < amplitude_criteria;   }), vector_metrics.end());
    return vector_metrics;
}

Metrics get_first(const std::vector<Metrics>& vector_metrics){
    return vector_metrics.front();
}


    
void CompressionResultsData::append(unsigned int k,
    TmId tmNumber,
    unsigned int amplitudes,
    double self_compression,
    double normalized_compression){
    
    this->kvalue.push_back(k);
    this->tmNumber.push_back(tmNumber);
    this->amplitude.push_back(amplitudes);
    this->self_compression.push_back(self_compression);
    this->normalized_compression.push_back(normalized_compression);

}

void CompressionResultsData::append_metrics(IndexAndMetrics indAndMetrics){
    
    this->tmNumber.push_back(indAndMetrics.tmNumber);
    this->kvalue.push_back(indAndMetrics.metrics.k);
    this->amplitude.push_back(indAndMetrics.metrics.amplitude);
    this->self_compression.push_back(indAndMetrics.metrics.selfCompression);
    this->normalized_compression.push_back(indAndMetrics.metrics.normalizedCompression);
}

void CompressionResultsData::clear_data(){
    this->kvalue.clear();
    this->tmNumber.clear();
    this->amplitude.clear();
    this->self_compression.clear();
    this->normalized_compression.clear();
}

void CompressionResultsData::merge(CompressionResultsData&& other){
    this->kvalue.insert(end(this->kvalue),begin(other.kvalue),end(other.kvalue));
    this->tmNumber.insert(end(this->tmNumber),begin(other.tmNumber),end(other.tmNumber));
    this->amplitude.insert(end(this->amplitude), begin(other.amplitude), end(other.amplitude));
    this->normalized_compression.insert(end(this->normalized_compression), begin(other.normalized_compression), end(other.normalized_compression));
    this->self_compression.insert(end(this->self_compression), begin(other.self_compression), end(other.self_compression));
}


AvgMetrics CompressionResultsData::avg(){
    AvgMetrics avgMetrics;
    avgMetrics.amp.first = std::accumulate( this->amplitude.begin(), this->amplitude.end(), 0.0)/this->amplitude.size();
    double sq_amp_sum = std::inner_product(this->amplitude.begin(), this->amplitude.end(), this->amplitude.begin(), 0.0);
    avgMetrics.amp.second = std::sqrt(sq_amp_sum / this->amplitude.size() - avgMetrics.amp.first * avgMetrics.amp.first);

    avgMetrics.sc.first = std::accumulate( this->self_compression.begin(),  this->self_compression.end(), 0.0)/ this->self_compression.size();
    double sq_sc_sum = std::inner_product(this->self_compression.begin(), this->self_compression.end(), this->self_compression.begin(), 0.0);
    avgMetrics.sc.second = std::sqrt(sq_sc_sum / this->self_compression.size() - avgMetrics.sc.first * avgMetrics.sc.first);

    avgMetrics.nc.first = std::accumulate( this->normalized_compression.begin(), this->normalized_compression.end(), 0.0)/this->normalized_compression.size();
    double sq_nc_sum = std::inner_product(this->normalized_compression.begin(), this->normalized_compression.end(), this->normalized_compression.begin(), 0.0);
    avgMetrics.nc.second = std::sqrt(sq_nc_sum / this->normalized_compression.size() - avgMetrics.nc.first * avgMetrics.nc.first);
    
    return avgMetrics;
}

void CompressionResultsData::print_profile_data(unsigned int divison){
    assert(this->amplitude.size()== this->self_compression.size() && 
    this->self_compression.size()== this->normalized_compression.size());


    std::cout<< "iterations \t amplitude \t Self-Compression \t Normalized Compression " << std::endl; 
    std::cout<< "---------------------------------------------------" <<std::endl;
    for (auto i = 0u; i < this->amplitude.size(); ++i) {
        std::cout << ((i + 1) * divison) << "\t" << this->amplitude[i] << "\t" << std::setprecision(5) << std::showpoint <<  this->self_compression[i] 
                  << "\t" << std::setprecision(5) << std::showpoint << this->normalized_compression[i] << "\t" << std::endl;
  }
}

void CompressionResultsData::print_data( unsigned int numIt){
    assert( this->tmNumber.size()==this->amplitude.size() && 
    this->amplitude.size()==this->kvalue.size() && 
    this->kvalue.size() == this->self_compression.size() && 
    this->self_compression.size()== this->normalized_compression.size());
    
    
    std::cout<< "TM \t k value \t iterations \t amplitude \t Self-Compression \t Normalized Compression " << std::endl; 
    std::cout<< "---------------------------------------------------" <<std::endl;
    for (auto i = 0u; i < this->amplitude.size(); ++i) {
    std::cout << this->tmNumber[i] << "\t" << this->kvalue[i] << "\t" << numIt << "\t" << this->amplitude[i] << "\t" 
    << std::setprecision(5)  << std::showpoint <<  this->self_compression[i] << "\t" << std::setprecision(5) 
    << std::showpoint << this->normalized_compression[i] << "\t" << std::endl;
    }
    std::cout<< "---------------------------------------------------" <<std::endl;
}

void CompressionResultsData::print_avg_metrics(AvgMetrics avgMetrics){
    std::cout<< "Number of TM \t Mean Amp+/-std \t Mean sc+/-std \t Mean nc+/-std" << std::endl;
    std::cout <<  this->amplitude.size() << "\t\t" << avgMetrics.amp.first << "+/-" << avgMetrics.amp.second 
                                              << "\t\t" << avgMetrics.sc.first << "+/-" << avgMetrics.sc.second 
                                              << "\t" << avgMetrics.nc.first << "+/-" << avgMetrics.nc.second
                                              << std::endl;

}

