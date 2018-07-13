#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <math.h> 
#include <map>
#include <algorithm>
#include <set>
#include "Point.h"
#include "Node.h"
#include "Graph.h"

Graph::Graph() {
}

Graph::Graph(const Graph& orig) {
}

int Graph::add(Node *n) {
    int i = graph.size();
    graph.push_back(n);
    return i;
}

Node *Graph::at(int i) {
    return graph.at(i);
}

void Graph::addLink(int i, int link) {
    graph.at(i)->next(link);
    graph.at(link)->next(i);
}

int Graph::size() {
    return graph.size();
}

void Graph::display() {
    cout << "Nodes: " << graph.size() << endl;
    for (int i = 0; i < graph.size(); i++) {
        cout << "[" << i << "] ";
        graph.at(i)->display();
        cout << endl;
    }
}

void Graph::xmlNodes() {
    int k =1;
    int length = graph.size();
    //cout << "<nodes>";
    for (int i = 0; i < length; i++) {
        //cout << "<n>";
        cout << "No. " << k << " | "; 
        
        graph.at(i)->xmlNodeXY();
        
        cout << " | ";
        
        vector<int> neighbors = graph.at(i)->getNeighbors();
        int l = neighbors.size();
        for (int i=0; i<l; i++){
            cout << "<l>";
            cout  << graph.at(neighbors.at(i))->getPoint().GetX() << "," << graph.at(neighbors.at(i))->getPoint().GetY();
            cout << "</l>";
        }
        
        //cout << " | ";
        
        //cout << "<c>";
        //int color = graph.at(i)->getColor();
        cout << color;
        //cout << "</c>";
        
        cout << " | ";
        
        //cout << "<s>";
        //string signature = graph.at(i)->vecToString();
        string signature = graph.at(i)->listToString();
        //cout << signature;
        //cout << "</s>";
        //cout << "</n>";
                
        cout << signature << endl;
        k++;
        
    }
    //cout << "</nodes>";
}