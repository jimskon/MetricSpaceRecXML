/* 
 * File:   Graph.h
 * Author: skonjp
 *
 * Created on August 30, 2017, 12:13 AM
 */

#ifndef GRAPH_H
#define GRAPH_H
#include "Node.h"

class Graph {
public:
    Graph();
    Graph(const Graph& orig);

    int add(Node *n);
    void addLink(int i, int link);
    int size();
    Node *at(int i);
    void display();
    void xmlNodes();
private:
    vector<Node*> graph;
};

#endif /* GRAPH_H */