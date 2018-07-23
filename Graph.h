#ifndef GRAPH_H
#define GRAPH_H
#include "Node.h"

class Graph {
public:
    Graph();
    Graph(const Graph& orig);

    int add(Node *n);
    void addLink(int i, int link);
    
    Node *at(int i);
    
    int size();
    
    void xmlNodes();
    void CSVData();
private:
    vector<Node*> graph;
};

#endif /* GRAPH_H */