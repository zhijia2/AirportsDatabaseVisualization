# Final Project Proposal ([zhijia2-qic7-zhichao8](https://github-dev.cs.illinois.edu/cs225-sp21/zhijia2-qic7-zhichao8))

## Leading Question

This project has four goals: 1) confirm the weights which be used for the graph. 2) using the shortest path algorithm to find preferred routes between any two airports. 3) generate a graphical output onto which projected onto a world map 4) using betweenness centrality mapping what airports are most important

## Dataset Acquisition and Processing

For this project, we are going to use OpenFlights as our dataset, which is provided on the official website of the CS225 Final Project dataset. For the format of the dataset file, it is originally provided in a \*.dat format, and we plan to convert it into a vector format to better handle the content inside. The attributes we will use from the dataset are mostly from routes subsets provided. Later on, we may fortify the program to use the airport subset for marking routes on the map. As mentioned before, we&#39;d like to determine weight accordingly.

Since the dataset could contain implicit errors and other issues, we will endeavor to remove any problematic records while testing.

database link: [Airport, airline and route data](https://openflights.org/data.html)
## Graph Algorithms
**1. BFS (Breadth First Search) (used for traversal)**

**2. Dijkstra’s Algorithm(used for getting shortest path of every pair)**

**3. Graphic Output of Graph(project the data on to a map)**  

The traversal algorithm we&#39;d like to deploy is BFS according to the case we encountered. We will use them as an iterator to start from an input departing Airport, and end if no airports left. Operator++() will render the iterator to move to the next possible destination.  
**Input the starting airport(node) and return all airports(nodes) we can reach from the starting airport(node)**  

The shortest path algorithm we will use Dijkstra&#39;s Algorithm    
**Input the start airport(node) and the end airport(node), then returns the shortest path from the start airport(node) to the airport(node).** 

As for the complex or uncovered options, we will use Graphical output projected onto a world map.   
**Input the data, thie output is projecting the shortest path onto the map.**

## Timeline

April 9 - submit a project proposal and team contract

April 12 - set up initial repository and Makefile

April 15 - finish reading in data into array format

April 19 - convert array format into graph format

April 22 - write BFS iterator

April 29 - write Dijkstra's and verify with tests

May 5 - write graph projection onto World Map and verify with tests

May 7 - finish report

May 9 - sync to record the final presentation

May 11 - finish editing presentation and submit
