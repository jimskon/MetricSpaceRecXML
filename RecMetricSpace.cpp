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
#include "Node.h"
#include "Point.h"
#include "Graph.h"

using namespace std;
static int DIVIDEFACTOR = 4;
int maxColorsUsed=0;

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

string sigToString(vector<int> signature) {   
    std::ostringstream vss;
    
    if (!signature.empty()) 
    {
    // Convert all but the last element to avoid a trailing ","
    std::copy(signature.begin(), signature.end()-1, std::ostream_iterator<int>(vss, ","));

    // Now add the last element with no delimiter
    vss << signature.back();
    }
    
    return vss.str();
}

Point computeP2(Point pStart, Point pEnd) {
    int x = (3 * pStart.GetX() + pEnd.GetX()) / DIVIDEFACTOR;
    int y = (3 * pStart.GetY() + pEnd.GetY()) / DIVIDEFACTOR;
    Point p(x, y);
    return p;
}

Point computeP3(Point pStart, Point pEnd) {
    int x = (pStart.GetX() + pEnd.GetX()) / 2 + (pEnd.GetY() - pStart.GetY()) / DIVIDEFACTOR;
    int y = (pStart.GetY() + pEnd.GetY()) / 2 - (pEnd.GetX() - pStart.GetX()) / DIVIDEFACTOR;
    Point p(x, y);
    return p;
}

Point computeP4(Point pStart, Point pEnd) {
    int x = (pStart.GetX() + pEnd.GetX()) / 2 - (pEnd.GetY() - pStart.GetY()) / DIVIDEFACTOR;
    int y = (pStart.GetY() + pEnd.GetY()) / 2 + (pEnd.GetX() - pStart.GetX()) / DIVIDEFACTOR;
    Point p(x, y);
    return p;
}

Point computeP5(Point pStart, Point pEnd) {
    int x = (pStart.GetX() + 3 * pEnd.GetX()) / DIVIDEFACTOR;
    int y = (pStart.GetY() + 3 * pEnd.GetY()) / DIVIDEFACTOR;
    Point p(x, y);
    return p;
}

void clearDists(Graph *g) {
    for (int i = 0; i < g->size(); i++) {
        g->at(i)->clearDist();
    }
}

// Recursively set the distances of all nodes adjacent to this node
// as long as distance <= MAX
void getNodesInRange(Graph *g, set<int> &inRange, int index, int max) {
    int dist = g->at(index)->getDist(); // Distance of this node
    //cout << "Node: " << index << " Dist: " << dist << endl;
    if (dist < INT_MAX && dist > max) return; //  This is the base case for recursion - we have reached the max
    //cout << "Add: " << index << endl;
    inRange.insert(index);
    // we can go deeper, recurse on neighbors if they are farther away then our length + 1
    for (int i = 0; i < g->at(index)->getNeighbors().size(); i++) { // For each neighbor
        int j = g->at(index)->getNeighbors().at(i); // Get the neighbors index
        if (g->at(j)->getDist() > dist + 1) {
            (g->at(j))->setDist(dist + 1);
            getNodesInRange(g, inRange, j, max);
        }
    }
}

// Find all nodes within max range
set<int> findNodesInRange(Graph *g, int startIndex, int max) {
    set<int> ball; // Nodes in ball of max diameter
    clearDists(g); // reset distances
    g->at(startIndex)->setDist(0);
    getNodesInRange(g, ball, startIndex, max);
    return ball;
}

// Color center of balls with a given ballsize

void colorBallsWithBallSize(Graph *g, int ballSize) {
    int maxDist = 10;
    /*do {
        cout << "Node to check[0.." << g->size() - 1 << "] (-1 to end): ";
        cin >> node;
    } while (node < 0 && node >= g->size()); */
    //int maxBall = 0;
    for (int i = 0; i < g->size(); i++) {
        set<int> ball = findNodesInRange(g, i, maxDist);
        //maxBall = max(maxBall, ball.size());
        if (ball.size() >= ballSize) {
            g->at(i)->setColor(1);
            //cout << i << " ";
        }
    }
    //cout << "Max ball size: " << maxBall << endl;
}

// Fill set with maxColors colors (ints)

void initColors(set<int> &colors, int maxColors) {
    for (int i = 1; i <= maxColors; i++) {
        colors.insert(i);
    }
}


void removeUsedColors(Graph *g, set<int> &colors, set<int> ball) {
    set<int>::iterator it;
    for (it = ball.begin(); it != ball.end(); ++it) {
        int index = *it;
        int color = g->at(index)->getColor();
        if (color > 0) {
            colors.erase(color);
        }
    } 
}
void colorAllNodes(Graph *g, int maxDist) {
    
    const int MaxColors = 65;
    set<int> colors; //set of currently available colors
    set<int>::iterator it;
    
    for (int i = 0; i < g->size(); i++) {
        set<int> ball = findNodesInRange(g, i, maxDist);

        initColors(colors, MaxColors);
        removeUsedColors(g, colors, ball);
        it=colors.begin();
        
        g->at(i)->setColor(*it);
        maxColorsUsed = (maxColorsUsed>*it) ? maxColorsUsed : *it;
        //g->at(i)->setColor(1);
    }
}

void displayBall(Graph *g, set<int> ball) {
    cout << "Size of ball: " << ball.size() << endl;
    set<int>::iterator it;
    for (it = ball.begin(); it != ball.end(); ++it) {
        cout << ' ' << *it;
    }
    cout << '\n';
}

int getNeg(int v) {
    return (-1)*v;
}

// Creates all of the nodes, links, and signatures.
void createGroup(Node *n1, Node *n6, int level, int sigLen, Graph *g, int &si, int &fi) {    
    // Links the nodes
    if (level == 0) {  
        if (si < 0) {
            si = g->add(n1);
        }
        if (fi < 0) {
            fi = g->add(n6);
        }
        g->addLink(si, fi);
        return;
    }
    
    // Creates four new nodes that are between the end points.
    Node *n2 = new Node(computeP2(n1->getPoint(), n6->getPoint()));
    Node *n3 = new Node(computeP3(n1->getPoint(), n6->getPoint()));
    Node *n4 = new Node(computeP4(n1->getPoint(), n6->getPoint()));
    Node *n5 = new Node(computeP5(n1->getPoint(), n6->getPoint()));
    
    // Creates the signature for the nodes.
    vector<int> ts = n1->getSig();
    
    while (ts.size() >= sigLen) {
        ts.pop_back();
    }
    
    // Assigns (-1) to the point in the signature that should be going down.
    int j=0;
    while(j < ts.size()) {
        if ( (n6->getSig().at(j) < 0 && ts.at(j) > 0)) {
            ts.at(j) = -1;
            break;
        } 
        j++;   
    }
    
    if (n1->size() < sigLen) {
        n1->pushSig(0);
    }
        
    if (n6->size() < sigLen) {
        n6->pushSig(0);
    }
        
    n2->copySig(ts);
    n3->copySig(ts);
    n4->copySig(ts);
    n5->copySig(ts);
    
    n2->pushSig(1);
    n3->pushSig(2);
    n4->pushSig(-2);
    n5->pushSig(3);
    
    int b = -1, c = -1, d = -1, e = -1;
    
    // Repeat the process until all nodes are accounted for.
    createGroup(n1, n2, level - 1, sigLen+1, g, si, b);
    createGroup(n2, n3, level - 1, sigLen+1, g, b, c);
    createGroup(n2, n4, level - 1, sigLen+1, g, b, d);
    createGroup(n3, n5, level - 1, sigLen+1, g, c, e);
    createGroup(n4, n5, level - 1, sigLen+1, g, d, e);
    createGroup(n5, n6, level - 1, sigLen+1, g, e, fi);
    
}

// Create all levels (and nodes) between these two nodes. Point first to the 
// first point in the created group.
void createMetricSpace(Node *n1, Node *n2, int l, Graph *g) {
    
    if (l < 1) {
        cout << "Levels must be at least one" << endl;
        return;
    }
    
    int si = -1;
    int fi = -1;
    
    n1->pushSig(0);
    n2->pushSig(1);
    
    createGroup(n1, n2, l - 1, 2, g, si, fi);
    
}

// Create 
int main() {
    Graph *g = new Graph();
    int levels;

    Point pStart(0, 250);
    Point pEnd(1000, 250);

    Node *n1 = new Node(pStart);
    Node *n2 = new Node(pEnd);

    cout << "How many levels? ";
    cin >> levels;

    createMetricSpace(n1, n2, levels, g);
    cout << "Done creating, size: " << g->size() << endl;

    //g->xmlNodes();
    
    int node = 1;
    int size;
    
    //colorBallsWithBallSize(g, 64);
    
    colorAllNodes(g,10);
    g->xmlNodes();
    
    cout << endl << "Highest Color: " << maxColorsUsed << endl;
    
    //g->display();

    return 0;
}