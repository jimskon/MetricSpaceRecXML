#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>
#include <list>
#include <math.h> 
#include <map>
#include <limits>
#include "Node.h"

// This is the default constructor for generating a new node. Every single node 
// that is generated will be run through this constructor to initialize the 
// following variables.
// - - -
// Each parameter stands for - 
// c = color
// s = signature
// p = (x , y) coordinates
Node::Node(int c, list<int> s, Point p) {
    color = c;
    
    this->sigLis = s;
        
    this->p = p;
}

// Records the neighbors of a node by pushing them back into a vector<int>
void Node::next(int i) {
    this->neighbors.push_back(i);
}

// Returns the (x , y) coordinates.
Point Node::getPoint() {
    return p;
}

// Displays the (x , y) coordinates.
void Node::xmlNodeXY() {
    cout << "<x>" << p.GetX() << "</x><y>" << p.GetY() << "</y>";
}

// Returns the neighbors of a node. (i.e. the very first node only has one
// neighbor, hence the node to the immediate right is sent back to the user.)
vector<int> Node::getNeighbors() {
    return neighbors;
}

// Returns the color (int) of the node.
int Node::getColor() {
    return color;
}

// Return the size of the signature.
int Node::sizeSig() {
    return sigLis.size();
}

// Returns the signature.
list<int> Node::getSig() {
    return sigLis;
}

// Adds a number to the ending of signature.
void Node::pushSigBack(int v) {
    sigLis.push_back(v);
}

// Adds two numbers to the ending of signature.
void Node::pushSigBack2(int x, int y) {
    sigLis.push_back(x);
    sigLis.push_back(y);
}

// Converts a list<int> into a string.
string Node::listToString() {
    std::ostringstream out;
    
    if (!sigLis.empty()) {
        // Convert all but the last element to avoid a trailing ","
        copy(sigLis.begin(), --sigLis.end(), ostream_iterator<int>(out, ","));

        // Now add the last element with no delimiter
        out << sigLis.back();
    }
    
    return out.str();
}
