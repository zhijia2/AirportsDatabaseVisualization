#pragma once

#include<map>
#include<set>
#include<vector>
#include<cmath>
#include<string>
#include "airport.h"
#include "datReader.h"


using namespace std;
typedef pair<string, float> weightedPATH;

class Graph{
    public:
    Graph();
    Graph(std::map<std::string, std::map<string , float>>adj_);
    vector<string>BFS(string start, std::map<std::string, std::map<string , float>> adj_);
    void addEdge(string start, string end, float weight);
    std::vector<string> Dijkstras(string start, string end);
    float distance(std::vector<string> path);
    float getweight(airport start, airport end);//calculate the weight of a route
    

    private:
    std::map<std::string, std::map<string , float>> adj;
};
