#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "datReader.h"
#include "airport.h"
#include "Graph.h"
using namespace std;
void datReader::clear() {
        eachLine.clear();
}
vector<datReader::path> datReader::getPathDATA() {
        std::map<std::string,airport >nodes = getnodes();
        clear();
        ifstream file("data/routes.dat");
        string str;
        while (std::getline(file, str)) {
                eachLine.push_back(str);
        }
        vector<datReader::path> pathDATA;
        if (eachLine.empty()) return pathDATA; //if empty: return empty vector
        for (auto it : eachLine) {
                vector<string> commaSeperated;
                stringstream ss(it);
                string str;
                while (getline(ss, str, ',')) {
                        commaSeperated.push_back(str);
                }
                string source = commaSeperated[2];
                string destination = commaSeperated[4];
                // for (auto its : pathDATA) {
                //         if (its.source == source && its.destination == destination) continue;
                // } 
                double weight = getweight(nodes[source],nodes[destination]);
                datReader::path eachPath = path(source, destination, weight);
                pathDATA.push_back(eachPath);
        }
        return pathDATA;
}

double datReader::getweight(airport start, airport end){

//the basic number
        double startLat = start.lat* M_PI / 180.0;
        double startLong = start.lon* M_PI / 180.0;
        double endLat = end.lat* M_PI / 180.0;
        double endLong = end.lon* M_PI / 180.0;
        double dist = pow(sin((endLat-startLat)/2), 2) + cos(startLat)*cos(endLat)*pow(sin((endLong-startLong)/2), 2); 
        dist = 2*asin(sqrt(dist));
        dist = dist*6371;

        return dist;
}



vector<airport> datReader::getSplitAirportDATA() {
        clear();
        ifstream file("data/airports.dat");
        string str;
        while (std::getline(file, str)) {
                eachLine.push_back(str);
        }
        vector<airport> airportSplitDATA;
        if (eachLine.empty()) return airportSplitDATA; //if empty: return empty vector
        for (auto it : eachLine) {
                vector<string> commaSeperated;
                stringstream ss(it);
                string str;
                while (getline(ss, str, ',')) {
                        commaSeperated.push_back(str);
                }
                string IATA = commaSeperated[4].substr(1, 3);
                if (IATA.length() != 3) continue;
                airport eachAirport = airport(IATA, commaSeperated[6], commaSeperated[7]);
                airportSplitDATA.push_back(eachAirport);
        }
        return airportSplitDATA;
}

std::map<std::string, airport> datReader::getnodes() {
        std::map<std::string,airport >nodes;
        vector<airport> airportSplitDATA = getSplitAirportDATA();
        for (auto i: airportSplitDATA){
                nodes[i.IATA] = i;
        }
        return nodes;
}
