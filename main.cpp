#include <iostream>
#include <vector>
#include <string>
#include "datReader.h"
#include "airport.h"
#include "image.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Graph.h"
#include <stdlib.h> 
#include <fstream>
#include <unordered_map>

using namespace cs225;
using namespace std;
int main() {
        srand(time(NULL));
        //data read in 
        datReader reader;
        vector<datReader::path> edge = reader.getPathDATA(); // read "data/routes.dat"
        reader.clear();
        vector<airport> airportSplitDATA = reader.getSplitAirportDATA(); // read "data/airports.dat"

        //generate adjacency matrix
        std::map<std::string, std::map<string , float>> adj; // adjacency matrix
        for (auto i : edge) {
                adj[i.source][i.destination] = i.weight; // generate adjacency matrix using routes data
        }

        // Dijkstras's algorithm (project goal #2) (Graph Algorithms #2)
        string start;
        string end;
        Graph* g = new Graph(adj);
        std::cout<< "Enter the source IATA airport." << endl;
        std::cin >> start;
        transform(start.begin(), start.end(), start.begin(),
                ::toupper);
        std::cout<< "Enter the destination IATA airport." << endl;
        std::cin >> end;
        transform(end.begin(), end.end(), end.begin(),
                ::toupper);
        // string start = "ZYL"; // Dijkstras's shortest path: starting point example(IATA of an airport)
        // string end = "ZVK"; // Dijkstras's shortest path: ending point example(IATA of an airport)

        // uncomment the following code block to randomly generate starting point and ending point
        // int random = rand() % edge.size();
        // start = edge[random].source;
        // random = rand() % edge.size();
        // end = edge[random].source;

        cout << "starting point: " << start << "; ending point: " << end << endl; 
        std::vector<string> path = g->Dijkstras(start, end); // Dijkstras's algorithm
        for(auto i: path){
                cout<<i<<endl; // Dijkstras's algorithm output: path from starting point to ending point
        }
        float sum = g->distance(path); // Dijkstras's algorithm output: shortest distance from starting point to ending point
        if(sum == 0) {cout << "You might input wrong source IATA or destination IATA or both of them"<< sum <<endl; return 0;}
        else cout << "shortest distance: "<< sum <<endl;
        
        // BFS demo: uncomment line 33 in "Graph.cpp" to see a demo; (Graph Algorithms #1)
        //while testing make test, please comment line 33 back to have a cleaner view.
        
        std::ofstream outfile;
        outfile.open("output.txt");
        string BFSstart = start;
        // cout<<"Perfomring BFS beginning at "<<BFSstart<<endl;
        // outfile<<"BFS beginning at "<<BFSstart<<":"<<endl;
        vector<string> bfs= g->BFS(BFSstart, adj); 
        for (auto i: bfs) {
                outfile<<i<<", ";
        }
        outfile<<endl;
        cout<<"BFS Complete"<<endl;
        

        // projection of routes and airports on a high-res world map (project goal #1,3) (Graph Algorithms #3)
        std::cout<< "Do you want see the ouput.png? reply yes or no" << endl;
        string input;
        std::cin >> input;
        if(input == "yes") {
                image* f = new image();
                PNG* out = f->createImage(airportSplitDATA, edge); // pass routes and airports, and project them on "data/map.png"    
                out->writeToFile("output.png"); // output named "output.png" (2400*1200)
                cout<<"output.png Complete"<<endl;
        }
        
}
     