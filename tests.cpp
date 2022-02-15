#include <string>
#include <vector>
#include <utility>
#include "cs225/catch/catch.hpp"
#include "datReader.h"
#include "airport.h"
#include "image.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Graph.h"
#include <stdlib.h> 

bool validPath(string a, string b, std::vector<string> path, 
    std::map<std::string, std::map<string , float>> adj) {
    for (int i = 0; i < path.size()-1; i++) {
        // cout << "current path: " << path[i] << endl;
        // cout << "current a: " << a << endl;
        if (a != path[i]) return 0;
        if (adj[a].find(path[i+1]) == adj[a].end()) return 0;
        a = path[i+1];
    }
    if (b != path[path.size()-1]) return 0;
    return 1;
}

TEST_CASE("airports.dat is input properly") {
    vector<airport> airportSplitDATA;
    datReader reader;
    airportSplitDATA = reader.getSplitAirportDATA();
    reader.clear();
    REQUIRE(airportSplitDATA[0].IATA == "GKA");
    REQUIRE(airportSplitDATA[1].IATA == "MAG");
    REQUIRE(airportSplitDATA[2].IATA == "HGU");
}

TEST_CASE("route.dat is input properly") {
    vector<datReader::path> edge;
    datReader reader;
    edge = reader.getPathDATA();
    reader.clear();
    REQUIRE(edge[0].source == "AER");
    REQUIRE(edge[0].destination == "KZN");
    REQUIRE(edge[1].source == "ASF");
    REQUIRE(edge[1].destination == "KZN");
}

TEST_CASE("nodes is input properly") {
    std::map<std::string, airport> nodes;
    datReader reader;
    nodes = reader.getnodes();
    reader.clear();
    REQUIRE(nodes["GKA"].lat ==-6.081689834590001);
    REQUIRE(nodes["LAE"].lat ==-6.569803);
    REQUIRE(nodes["LAE"].lon ==146.725977);
}

TEST_CASE("BFS visited most of the nodes with tolerance 20") {
    vector<datReader::path> edge;
    datReader reader;
    edge = reader.getPathDATA();
    std::map<std::string, std::map<string , float>> adj;
    for (auto i : edge) {
            adj[i.source][i.destination] = i.weight;
    }
    Graph* g = new Graph(adj);
    string start = "ZYL";
    map<string, bool> visited = g->BFS(start, adj);
    cout << "visited: " << visited.size() << endl;
    cout << "adj: " << adj.size() << endl;
    int diff = adj.size() - visited.size();
    cout << "diff: " << diff << endl;
    REQUIRE(diff < 20);
}

TEST_CASE("BFS visited most of the nodes with tolerance 20; random test 100") {
    srand(time(NULL));
    vector<datReader::path> edge;
    datReader reader;
    edge = reader.getPathDATA();
    std::map<std::string, std::map<string , float>> adj;
    for (auto i : edge) {
            adj[i.source][i.destination] = i.weight;
    }
    Graph* g = new Graph(adj);
    for (int i = 0; i < 100; i++) {
        int random = rand() % edge.size();
        string start = edge[random].source;
        map<string, bool> visited = g->BFS(start, adj);
        cout << "start: " << start << endl;
        cout << "visited: " << visited.size() << endl;
        cout << "adj: " << adj.size() << endl;
        int diff = adj.size() - visited.size();
        cout << "diff: " << diff << endl;
        REQUIRE(diff < 40);
    }
}

TEST_CASE("shortest path from ZYL to LAE") {
    vector<datReader::path> edge;
    datReader reader;
    edge = reader.getPathDATA();

    std::map<std::string, std::map<string , float>> adj;
    for (auto i : edge) {
        adj[i.source][i.destination] = i.weight;
    }
    Graph* g = new Graph(adj);
    string start = "ZYL";
    string end = "LAE";
    std::vector<string> path = g->Dijkstras(start, end);       
    REQUIRE(validPath(start, end, path, adj));
}

TEST_CASE("shortest path random test 100") {
    srand(time(NULL));
    vector<datReader::path> edge;
    datReader reader;
    edge = reader.getPathDATA();

    std::map<std::string, std::map<string , float>> adj;
    for (auto i : edge) {
        adj[i.source][i.destination] = i.weight;
    }
    Graph* g = new Graph(adj);
    for (int i = 0; i < 100; i++) {
        int random = rand() % edge.size();
        string start = edge[random].source;
        random = rand() % edge.size();
        string end = edge[random].source;
        std::vector<string> path = g->Dijkstras(start, end);
        float sum = g->distance(path);       
        cout << "start: " << start << "; end: " << end << "; shortest distance: " << sum << endl;
        REQUIRE(validPath(start, end, path, adj));
    }
}

