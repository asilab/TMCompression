#include <iostream>     // std::cout
#include <fstream>      // std::fstream
#include <string>       // std::string
#include <sstream>      // std::istringstream
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

int main(int argc, char *argv[])
{   
    const std::string& input= argv[1];

    std::ifstream in;
    in.open(input);
    std::string line;
    
    

    std::vector <unsigned long long> tmVector;
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
            unsigned long long tm;
            unsigned int k;
            unsigned int iterations;
            unsigned int amplitude;
            double nmvc;
            double nc;

            std::istringstream iss(line); //put line into stringstream
            std::string word;
            while(iss >> tm >> k >> iterations >> amplitude >> nmvc >> nc) //read word by word
            {
                tmVector.push_back(tm);
                kVector.push_back(k);
                itVector.push_back(iterations);
                ampVector.push_back(amplitude);
                nmvcVector.push_back(nmvc);
                ncVector.push_back(nc);
            }
        }
    }
    auto nmvcit = std::max_element(std::begin(nmvcVector), std::end(nmvcVector));
    auto ampit = std::max_element(std::begin(ampVector), std::end(ampVector));


    for(auto& v : nmvcVector){ 
        nmvcVector2.push_back(v/(*nmvcit));
    } 
    for(auto& v : ampVector){ 
        ampVector2.push_back( static_cast<double>(v)/( *ampit ));
    } 

    for (auto i = 0u; i < tmVector.size(); ++i) {
        std::cout <<  tmVector[i] << "\t" << kVector[i] << "\t" << itVector[i] << "\t" 
         << std::setprecision(5) << std::showpoint <<  ampVector2[i]  << "\t" << nmvcVector2[i] << "\t"
         << ncVector[i] << std::endl;
    }
}
