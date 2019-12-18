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
    std::vector <TmId> tmVector;
    std::vector <unsigned int> kVector;
    std::vector <unsigned int> itVector;
    std::vector <unsigned int> ampVector;
    std::vector <double> ampVector2;
    std::vector <double> nmvcVector;
    std::vector <double> nmvcVector2;
    std::vector <double> ncVector;

    if(in.is_open())
    {


        while(std::getline(in, line)) //get 1 row as a string
        {
            std::string tm;
            unsigned int k;
            unsigned int it;
            double nmvc;
            double amplitude;
            double nc;
            
            //std::cout << line << std::endl;
            
            std::istringstream iss(line); //put line into stringstream
            
            
            while(iss >> tm >> k >> it >> amplitude >> nmvc >> nc) //read word by word
            {   
                //std::cout << tm << amplitude << nmvc << nc << std::endl;
                //exit(42);
                ampVector.push_back(amplitude);
                nmvcVector.push_back(nmvc);
                ncVector.push_back(nc);
            }
        }
    }

    
    auto sc_average = std::accumulate( nmvcVector.begin(), nmvcVector.end(), 0.0)/nmvcVector.size(); 
    auto amp_average = std::accumulate( ampVector.begin(), ampVector.end(), 0.0)/ampVector.size(); 
    auto nc_average = std::accumulate( ncVector.begin(), ncVector.end(), 0.0)/ncVector.size(); 

    std::cout <<  amp_average << std::setprecision(5) << std::showpoint << "\t" 
    << sc_average << std::setprecision(5) << std::showpoint << "\t" 
    << nc_average << std::setprecision(5) << std::showpoint << "\t" << std::endl;

}
