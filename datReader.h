#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "airport.h"

using namespace std;
class datReader {
        private:
                vector<string> eachLine;
        public:
                struct path {
                        string source;
                        string destination;
                        double weight;
                        path(string sourceIn, string destinationIn, double weight_) : source(sourceIn), destination(destinationIn), weight(weight_){
                      }   
                };
                vector<datReader::path> getPathDATA();
                vector<airport> getSplitAirportDATA();
                std::map<std::string, airport> getnodes();
                double getweight(airport start, airport end);
                void clear();
};

