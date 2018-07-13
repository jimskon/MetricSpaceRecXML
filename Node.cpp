/* 
 * File:   Node.cpp
 * Author: skonjp
 * 
 * Created on August 21, 2017, 10:33 AM
 */

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


Node::Node() {
    color = 0;
}

Node::Node(Point p) {
    color = 0;
    this->p = p;
}

Node::Node(int c, int n[], int s[], Point p) {
    color = c;
    int i=0;
    
    while (n[i] < INT_MAX) {
        neighbors.push_back(n[i++]);
    }
    
    i = 0;
    while (s[i] < INT_MAX) {
        sigLis.push_back(s[i++]);
        //signature.push_back(s[i++]);
    }
        
    this->p = p;
}

Node::~Node() {
}

void Node::display() {

    cout << " (" << p.GetX() << "," << p.GetY() << ") ";
    cout << "Color: " << color << " ";

    if (neighbors.size() > 0) {
        cout << "Next:";
    }
    int i = 0;
    while (i < neighbors.size()) {
        cout << neighbors.at(i) << ":";
        i++;
    }

}

void Node::next(int i) {
    this->neighbors.push_back(i);
}

Point Node::getPoint() {
    return p;
}

void Node::xmlNodeXY() {
    cout << "<x>" << p.GetX() << "</x><y>" << p.GetY() << "</y>";
}

vector<int> Node::getNeighbors() {
    return neighbors;
}

void Node::clearDist() {
    dist = INT_MAX;
}

void Node::setDist(int d) {
    dist = d;
}

int Node::getDist() {
    return dist;
}

void Node::setColor(int c) {
    color = c;
}

int Node::getColor() {
    return color;
}

// Converts a vector into a string.
string Node::vecToString() {
    std::ostringstream vss;
    
    if (!signature.empty()) {
        // Convert all but the last element to avoid a trailing ","
        std::copy(signature.begin(), signature.end()-1, std::ostream_iterator<int>(vss, ","));

        // Now add the last element with no delimiter
        vss << signature.back();
    }
    
    return vss.str();
}

// Returns the signature of a node.
vector<int> Node::getSig() {
    return signature;
}

// Pass in the level that you are looking at and return the vector but with  
// a new restricted size.
vector<int> Node::resize(int l) {
    signature.resize(l);
    return signature;
}

// Adds a number to a signature of a node.
void Node::pushSig(int v) {
    signature.push_back(v);
}

// Copy the signature of a vector onto a node.
void Node::copySig(vector<int> v) {
    this->signature = v; 
}

// Return the size of the signature.
int Node::size() {
    return signature.size();
}

void Node::vecToList() {
    copy( signature.begin(), signature.end(), back_inserter( sigLis ) );
}

int Node::sizeList() {
    return sigLis.size();
}

list<int> Node::getList() {
    return sigLis;
}

// Adds a number to the beginning of signature.
void Node::pushListFront(int v) {
    sigLis.push_front(v);
}

// Adds a number to the ending of signature.
void Node::pushListBack(int v) {
    sigLis.push_back(v);
}

// Removes the first element from a signature.
void Node::popListFront() {
    sigLis.pop_front();
}

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
