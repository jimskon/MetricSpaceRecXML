#ifndef NODE_H
#define NODE_H
#include <climits>
#include <list>
#include "Point.h"

using namespace std;

class Node {
public:
    
    Node(int c, list<int> s, Point p);
    
    void next(int i);

    Point getPoint();
    void xmlNodeXY();

    vector<int> getNeighbors();

    int getColor();
           
    int sizeSig();
    list<int> getSig();
    
    void pushSigBack(int v);
    void pushSigBack2(int x, int y);
    
    string listToString();

private:

    vector<int> neighbors;  
    
    // Stands for the signature in list formatting
    list<int> sigLis;
    
    Point p;
    int color;

};


#endif // NODE_H 