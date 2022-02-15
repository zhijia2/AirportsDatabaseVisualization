#include "Graph.h"
#include "datReader.h"
#include <queue>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <float.h>
#include <unordered_map>

using namespace std;
Graph::Graph() {
}

Graph::Graph(std::map<std::string, std::map<string , float>> adj_) {
    adj = adj_;
}

void Graph::addEdge(string start, string end, float weight){
    adj[start][end]=weight;
}


vector<string> Graph::BFS(string start, std::map<std::string, std::map<string , float>> adj_){
    unordered_map<string, bool> visited;
    vector<string> result;
    for (auto i : adj_) {
      visited[i.first] = false;
    }
    visited[start] = true;
    queue<string> q_;
    q_.push(start);
    while(!q_.empty()) {
       string s = q_.front(); 
       result.push_back(s);
    //    cout << s << endl;
       q_.pop();
       for (auto it: adj_[s]) {
           if (visited[it.first]==false) {
               visited[it.first] = true;
               q_.push(it.first);
           }
       }
    }
    return result;
}


std::vector<string> Graph::Dijkstras(string start, string end) {
    std::priority_queue<weightedPATH, std::vector<weightedPATH>, std::greater<weightedPATH>> pq;
    pq.push(make_pair(start,0));
    std::map<string, float> dist;
    for (auto i: adj) {
        dist[i.first] = DBL_MAX;
    }
    dist[start] = 0;
    std::map<string, bool> visited;
    for (auto i : adj) {
      visited[i.first] = false;
    }
    visited[start] = true;
    std::map<string, string> prev;
    std::vector<string> path;
    while (!pq.empty()) {
        string curairport = pq.top().first;
        pq.pop();
        std::map<string ,float>  adjEdges = adj[curairport];
        for (auto i : adjEdges) {
            string nextairport = i.first;
            if (visited[nextairport]) continue; 
            float edgeWeight = i.second;
            if (dist[nextairport] > dist[curairport] + edgeWeight) {
                dist[nextairport] = dist[curairport] + edgeWeight;
                pq.push(make_pair(nextairport,dist[nextairport]));
                prev[nextairport] = curairport;
            }
        }
        visited[curairport] = true;
    }
    string cur = end;
    for (cur = end; cur != prev[start]; cur = prev[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());
    return path;
}

float Graph::distance(std::vector<string> path) {
    float sum = 0;
    for (unsigned long i = 0; i < path.size()-1; i++) {
        sum = sum + adj[path[i]][path[i+1]];
    }
    return sum;
}
