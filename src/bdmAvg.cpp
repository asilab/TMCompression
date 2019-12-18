/**
    ioAverage.cpp
    Purpose: Program that reads txt file and outputs average amplitude and Bits Required and NC

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

int main(int argc, char *argv[])
{   
    const std::string& input= argv[1];
    
    std::ifstream in;
    in.open(input);
    std::string line;
    std::vector <double> ampVector;
    std::vector <double> bdmVector;
    std::vector <double> ncVector;

    if(in.is_open())
    {


        while(std::getline(in, line)) //get 1 row as a string
        {
            std::string tm;
            std::string a;
            double amp;
            std::string x;
            std::string y;
            double bdm;
            double nc;
            
            //std::cout << line << std::endl;
            
            std::istringstream iss(line); //put line into stringstream
            
            
            while(iss >> tm >> a >> x >> amp >> y >> nc >> bdm) //read word by word
            {   ampVector.push_back(amp);
                ncVector.push_back(nc);
                bdmVector.push_back(bdm);

            }
        }
    }

    

    double  amp_average = std::accumulate( ampVector.begin(), ampVector.end(), 0.0)/ampVector.size(); 
    double sq_amp_sum = std::inner_product(ampVector.begin(), ampVector.end(), ampVector.begin(), 0.0);
    auto amp_std = std::sqrt(sq_amp_sum / ampVector.size() - amp_average * amp_average);

    double  nc_average = std::accumulate( ncVector.begin(), ncVector.end(), 0.0)/ncVector.size();
    double sq_nc_sum = std::inner_product(ncVector.begin(), ncVector.end(), ncVector.begin(), 0.0);
    auto nc_std = std::sqrt(sq_nc_sum / ampVector.size() - nc_average * nc_average);

    auto bdm_average = std::accumulate( bdmVector.begin(), bdmVector.end(), 0.0)/bdmVector.size(); 
    double sq_bdm_sum = std::inner_product(bdmVector.begin(), bdmVector.end(), bdmVector.begin(), 0.0);
    auto bdm_std = std::sqrt(sq_bdm_sum / bdmVector.size() - bdm_average * bdm_average);

    std::cout <<  amp_average << std::setprecision(5) << std::showpoint << "+/-" << amp_std << std::setprecision(5) << std::showpoint << "\t" 
    << bdm_average << std::setprecision(5) << std::showpoint << "+/-" << bdm_std << std::setprecision(5) << std::showpoint<< "\t" 
    << nc_average << std::setprecision(5) << std::showpoint << "+/-" << nc_std << std::setprecision(5) << std::showpoint << "\t" << std::endl;

}
