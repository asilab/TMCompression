/**
    ioAverage.cpp
    Purpose: Program that reads txt file and outputs average growth of methods amplitude and Bits Required and NC

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#include <iostream>     // std::cout
#include <fstream>      // std::fstream
#include <string>       // std::string
#include <sstream>      // std::istringstream
#include <vector>
#include <numeric>      //std::accumulate
#include <algorithm>
#include <cmath>
#include <iomanip>
#include"tmId.h"


struct AverageGrowth{
    unsigned int index;
    double amp;
    double nmvc;
    double nc;
};

int main(int argc, char *argv[])
{   
    
    const std::string& input= argv[1];
    std::ifstream in;
    in.open(input);
    std::string line;
    std::vector<AverageGrowth> vector_results;
    AverageGrowth avg;
    if(in.is_open())
    {
        while(std::getline(in, line)) //get 1 row as a string
        {
            //std::cout << line << std::endl;
            std::istringstream iss(line); //put line into stringstream
            
            while(iss >> avg.index >> avg.amp >> avg.nmvc >> avg.nc) //read word by word
            {   
                vector_results.push_back(avg);
            }
        }
    }

    std::sort(vector_results.begin(),vector_results.end(), [](const AverageGrowth &x, const AverageGrowth &y){ return (x.index < y.index);});
    unsigned int value = vector_results[0].index;
    AverageGrowth growth;
    AverageGrowth average_growth;

    std::vector <AverageGrowth> results_vector;
    auto counter = 0;
    for (auto a = 0u; a<=vector_results.size(); ++a){
        if(vector_results[a].index==value){   
            growth.index = vector_results[a].index;
            growth.amp += vector_results[a].amp;
            growth.nc += vector_results[a].nc;
            growth.nmvc += vector_results[a].nmvc;
            ++counter;
        } 
        else{
        average_growth.index = growth.index;
        average_growth.amp = growth.amp/counter;
        average_growth.nmvc = growth.nmvc/counter;
        average_growth.nc = growth.nc/counter;
        
        results_vector.push_back(average_growth);
        growth.amp = 0;
        growth.nmvc = 0;
        growth.nc = 0;
        counter = 1;
        value = vector_results[a].index;
        }
    }
    for (auto idx_average:results_vector){
        std::cout <<  idx_average.index << "\t" 
        << idx_average.amp << std::setprecision(5) << std::showpoint << "\t" 
        << idx_average.nmvc << std::setprecision(5) << std::showpoint << "\t"  
        << idx_average.nc << std::setprecision(5) << std::showpoint << "\t" <<std::endl;
    }
}
