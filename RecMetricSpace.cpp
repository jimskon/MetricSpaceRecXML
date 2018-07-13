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
#include <climits>
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

void colorAllNodes(Graph *g, int maxDist, int level) {
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

// The variable abbreviations stand for -
// np = neighbor pieces
// st = signature

// The number associated with each np, st, and A/B are irrelevant since they just 
// serve as a way to distinguish each one from another.

// Note that this will hold for all of the functions containing np and st.

// The comments that have < _ , _ , _ > are the signature or signature grouping
// for each new node added that way there is a quick reference to what part of 
// a level 3 graph is being viewed.

// Recognizes the bool p as true or false and follows the code accordingly. So
// if the value is true, then piece A is initialized and created. And the same 
// holds true for piece B. All of the nodes are added to the graph so that 
// they can be viewed.
void buildLevel3(Graph *g, bool p, int s, int e) {
    int n;
        
    if (g->at(e)->getList().front() < 0) {
        n = -1;
    } else {
        n = g->at(s)->getList().front();
    }
    
    int A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17,
        A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29;
    
    int B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13, B14, B15, B16, B17,
        B18, B19, B20, B21, B22, B23, B24, B25, B26, B27, B28, B29;
    
    int npa2[] = {s, A3, A4, INT_MAX}, npa3[] = {A2, A5, INT_MAX}, npa4[] = {A2, A5, INT_MAX}, 
        npa5[] = {A3, A4, A6, INT_MAX}, npa6[] = {A5, A7, A12, INT_MAX}, npa7[] = {A6, A8, A9, INT_MAX}, 
        npa8[] = {A7, A10, INT_MAX}, npa9[] = {A7, A10, INT_MAX}, npa10[] = {A8, A9, A11, INT_MAX}, 
        npa11[] = {A10, A17, INT_MAX}, npa12[] = {A6, A13, A14, INT_MAX}, npa13[] = {A12, A15, INT_MAX}, 
        npa14[] = {A12, A15, INT_MAX}, npa15[] = {A13, A14, A16, INT_MAX}, npa16[] = {A15, A22, INT_MAX}, 
        npa17[] = {A11, A18, A19, INT_MAX}, npa18[] = {A17, A20, INT_MAX}, npa19[] = {A17, A20, INT_MAX}, 
        npa20[] = {A18, A19, A21, INT_MAX}, npa21[] = {A20, A25, A26, INT_MAX}, npa22[] = {A16, A23, A24, INT_MAX}, 
        npa23[] = {A22, A25, INT_MAX}, npa24[] = {A22, A25, INT_MAX}, npa25[] = {A23, A24, A21, INT_MAX}, 
        npa26[] = {A21, A27, A28, INT_MAX}, npa27[] = {A26, A29, INT_MAX}, npa28[] = {A26, A29, INT_MAX}, 
        npa29[] = {A27, A28, e, INT_MAX};
    
    int npb2[] = {s, B3, B4, INT_MAX}, npb3[] = {B2, B5, INT_MAX}, npb4[] = {B2, B5, INT_MAX}, 
        npb5[] = {B3, B4, B6, INT_MAX}, npb6[] = {B5, B7, B12, INT_MAX}, npb7[] = {B6, B8, B9, INT_MAX}, 
        npb8[] = {B7, B10, INT_MAX}, npb9[] = {B7, B10, INT_MAX}, npb10[] = {B8, B9, B11, INT_MAX}, 
        npb11[] = {B10, B17, INT_MAX}, npb12[] = {B6, B13, B14, INT_MAX}, npb13[] = {B12, B15, INT_MAX}, 
        npb14[] = {B12, B15, INT_MAX}, npb15[] = {B13, B14, B16, INT_MAX}, npb16[] = {B15, B22, INT_MAX}, 
        npb17[] = {B11, B18, B19, INT_MAX}, npb18[] = {B17, B20, INT_MAX}, npb19[] = {B17, B20, INT_MAX}, 
        npb20[] = {B18, B19, B21, INT_MAX}, npb21[] = {B20, B25, B26, INT_MAX}, npb22[] = {B16, B23, B24, INT_MAX}, 
        npb23[] = {B22, B25, INT_MAX}, npb24[] = {B22, B25, INT_MAX}, npb25[] = {B23, B24, B21, INT_MAX}, 
        npb26[] = {B21, B27, B28, INT_MAX}, npb27[] = {B26, B29, INT_MAX}, npb28[] = {B26,B29, INT_MAX}, 
        npb29[] = {B27, B28, e, INT_MAX};

    
    int st1 [] = {n,0,1, INT_MAX}, st2 [] = {n,0,2, INT_MAX}, st3 [] = {n,0,-2, INT_MAX},
        st4 [] = {n,0,3, INT_MAX}, st5 [] = {n,1,0, INT_MAX}, st6 [] = {n,1,1, INT_MAX},
        st7 [] = {n,1,2, INT_MAX}, st8 [] = {n,1,-2, INT_MAX}, st9 [] = {n,1,3, INT_MAX},
        st10[] = {n,2,0, INT_MAX}, st11[] = {n,-1,1, INT_MAX}, st12[] = {n,-1,2, INT_MAX},
        st13[] = {n,-1,-2, INT_MAX}, st14[] = {n,-1,3, INT_MAX}, st15[] = {n,-2,0, INT_MAX},
        st16[] = {n,2,1, INT_MAX}, st17[] = {n,2,2, INT_MAX}, st18[] = {n,2,-2, INT_MAX},
        st19[] = {n,2,3, INT_MAX}, st20[] = {n,3,0, INT_MAX}, st21[] = {n,-2,1, INT_MAX},
        st22[] = {n,-2,2, INT_MAX}, st23[] = {n,-2,-2, INT_MAX}, st24[] = {n,-2,3, INT_MAX},
        st25[] = {n,3,1, INT_MAX}, st26[] = {n,3,2, INT_MAX}, st27[] = {n,3,-2, INT_MAX},
        st28[] = {n,3,3, INT_MAX};
    
    // Piece 3A
    if (p == true) {
        
        /*if (g->at(s)->getNeighbors().front() == 0) {
            g->at(s)->getNeighbors().pop_back();
            g->at(s)->getNeighbors().push_back(A2); // B2
        } else {
            g->at(s)->getNeighbors().pop_back();
            g->at(s)->getNeighbors().push_back(A29); // B29
        }*/2
        
        // <0,1,0>
        A6  =  g->add(new Node(6,  npa6, st5,  computeP2(g->at(s)->getPoint(), g->at(e)->getPoint())));
        
        // <0,2,0>
        A11 =  g->add(new Node(11, npa11, st10, computeP3(g->at(s)->getPoint(), g->at(e)->getPoint())));
        
        // <0,-2,0>
        A16 =  g->add(new Node(16, npa16, st15, computeP4(g->at(s)->getPoint(), g->at(e)->getPoint())));
        
        // <0,3,0>
        A21 =  g->add(new Node(2,  npa21, st20, computeP5(g->at(s)->getPoint(), g->at(e)->getPoint())));
        
        // Segment between <0,0,0> and <0,1,0>
        A2 =   g->add(new Node(36, npa2, st1,  computeP2(g->at(s)->getPoint(), g->at(A6)->getPoint()))); 
        A3  =  g->add(new Node(3,  npa3, st2,  computeP3(g->at(s)->getPoint(), g->at(A6)->getPoint())));
        A4  =  g->add(new Node(4,  npa4, st3,  computeP4(g->at(s)->getPoint(), g->at(A6)->getPoint())));
        A5  =  g->add(new Node(5,  npa5, st4,  computeP5(g->at(s)->getPoint(), g->at(A6)->getPoint())));
        
        // Segment between <0,1,0> and <0,2,0>
        A7  =  g->add(new Node(7,  npa7, st6,  computeP2(g->at(A6)->getPoint(), g->at(A11)->getPoint())));
        A8  =  g->add(new Node(8,  npa8, st7,  computeP3(g->at(A6)->getPoint(), g->at(A11)->getPoint())));
        A9  =  g->add(new Node(9,  npa9, st8,  computeP4(g->at(A6)->getPoint(), g->at(A11)->getPoint())));
        A10 =  g->add(new Node(10, npa10, st9,  computeP5(g->at(A6)->getPoint(), g->at(A11)->getPoint())));
        
        // Segment between <0,-1,0> and <0,-2,0>
        A12 =  g->add(new Node(12, npa12, st11, computeP2(g->at(A6)->getPoint(), g->at(A16)->getPoint())));
        A13 =  g->add(new Node(13, npa13, st12, computeP3(g->at(A6)->getPoint(), g->at(A16)->getPoint())));
        A14 =  g->add(new Node(14, npa14, st13, computeP4(g->at(A6)->getPoint(), g->at(A16)->getPoint())));
        A15 =  g->add(new Node(15, npa15, st14, computeP5(g->at(A6)->getPoint(), g->at(A16)->getPoint())));

        // Segment between <0,2,0> and <0,3,0>
        A17 =  g->add(new Node(17, npa17, st16, computeP2(g->at(A11)->getPoint(), g->at(A21)->getPoint())));
        A18 =  g->add(new Node(18, npa18, st17, computeP3(g->at(A11)->getPoint(), g->at(A21)->getPoint())));
        A19 =  g->add(new Node(19, npa19, st18, computeP4(g->at(A11)->getPoint(), g->at(A21)->getPoint())));
        A20 =  g->add(new Node(1,  npa20, st19, computeP5(g->at(A11)->getPoint(), g->at(A21)->getPoint())));
        
        // Segment between <0,-2,0> and <0,3,0>
        A22 =  g->add(new Node(20, npa22, st21, computeP2(g->at(A16)->getPoint(), g->at(A21)->getPoint())));
        A23 =  g->add(new Node(21, npa23, st22, computeP3(g->at(A16)->getPoint(), g->at(A21)->getPoint())));
        A24 =  g->add(new Node(22, npa24, st23, computeP4(g->at(A16)->getPoint(), g->at(A21)->getPoint())));
        A25 =  g->add(new Node(23, npa25, st24, computeP5(g->at(A16)->getPoint(), g->at(A21)->getPoint())));
        
        // Segment between <0,3,0> and <1,0,0>
        A26 =  g->add(new Node(30, npa26, st25, computeP2(g->at(A21)->getPoint(), g->at(e)->getPoint())));
        A27 =  g->add(new Node(32, npa27, st26, computeP3(g->at(A21)->getPoint(), g->at(e)->getPoint())));
        A28 =  g->add(new Node(33, npa28, st27, computeP4(g->at(A21)->getPoint(), g->at(e)->getPoint())));
        A29 =  g->add(new Node(34, npa29, st28, computeP5(g->at(A21)->getPoint(), g->at(e)->getPoint())));
        
        // Links the nodes in the graph.
        g->addLink(s, A2);
        g->addLink(A2, A3);
        g->addLink(A2, A4);
        g->addLink(A3, A5);
        g->addLink(A4, A5);
        g->addLink(A5, A6);
        g->addLink(A6, A7);
        g->addLink(A7, A8);
        g->addLink(A7, A9);
        g->addLink(A8, A10);
        g->addLink(A9, A10);
        g->addLink(A10, A11);
        g->addLink(A6, A12);
        g->addLink(A12, A13);
        g->addLink(A12, A14);
        g->addLink(A13, A15);
        g->addLink(A14, A15);
        g->addLink(A15, A16);
        g->addLink(A11, A17);
        g->addLink(A17, A18);
        g->addLink(A17, A19);
        g->addLink(A18, A20);
        g->addLink(A19, A20);
        g->addLink(A20, A21);
        g->addLink(A16, A22);
        g->addLink(A22, A23);
        g->addLink(A22, A24);
        g->addLink(A23, A25);
        g->addLink(A24, A25);
        g->addLink(A25, A21);
        g->addLink(A21, A26);
        g->addLink(A26, A27);
        g->addLink(A26, A28);
        g->addLink(A27, A29);
        g->addLink(A28, A29);
        g->addLink(A29, e);
                
    } else { // Piece B
                
        // <0,1,0>
        B6  =  g->add(new Node(15, npb6, st5,  computeP2(g->at(s)->getPoint(), g->at(e)->getPoint())));
        
        // <0,2,0>
        B11 =  g->add(new Node(5,  npb11, st10, computeP3(g->at(s)->getPoint(), g->at(e)->getPoint())));
        
        // <0,-2,0>
        B16 =  g->add(new Node(2,  npb16, st15, computeP4(g->at(s)->getPoint(), g->at(e)->getPoint())));
        
        // <0,3,0>
        B21 =  g->add(new Node(10, npb21, st20, computeP5(g->at(s)->getPoint(), g->at(e)->getPoint())));
        
        // Segment between <0,0,0> and <0,1,0>
        B2 =   g->add(new Node(24, npb2, st1,  computeP2(g->at(s)->getPoint(), g->at(B6)->getPoint()))); 
        B3  =  g->add(new Node(25, npb3, st2,  computeP3(g->at(s)->getPoint(), g->at(B6)->getPoint())));
        B4  =  g->add(new Node(26, npb4, st3,  computeP4(g->at(s)->getPoint(), g->at(B6)->getPoint())));
        B5  =  g->add(new Node(16, npb5, st4,  computeP5(g->at(s)->getPoint(), g->at(B6)->getPoint())));
        
        // Segment between <0,1,0> and <0,2,0>
        B7  =  g->add(new Node(18, npb7, st6,  computeP2(g->at(B6)->getPoint(), g->at(B11)->getPoint())));
        B8  =  g->add(new Node(20, npb8, st7,  computeP3(g->at(B6)->getPoint(), g->at(B11)->getPoint())));
        B9  =  g->add(new Node(22, npb9, st8,  computeP4(g->at(B6)->getPoint(), g->at(B11)->getPoint())));
        B10 =  g->add(new Node(6,  npb10, st9,  computeP5(g->at(B6)->getPoint(), g->at(B11)->getPoint())));
        
        // Segment between <0,-1,0> and <0,-2,0>
        B12 =  g->add(new Node(19, npb12, st11,  computeP2(g->at(B6)->getPoint(), g->at(B16)->getPoint())));
        B13 =  g->add(new Node(21, npb13, st12,  computeP3(g->at(B6)->getPoint(), g->at(B16)->getPoint())));
        B14 =  g->add(new Node(23, npb14, st13,  computeP4(g->at(B6)->getPoint(), g->at(B16)->getPoint())));
        B15 =  g->add(new Node(7,  npb15, st14,  computeP5(g->at(B6)->getPoint(), g->at(B16)->getPoint())));

        // Segment between <0,2,0> and <0,3,0>
        B17 =  g->add(new Node(35, npb17, st16,  computeP2(g->at(B11)->getPoint(), g->at(B21)->getPoint())));
        B18 =  g->add(new Node(13, npb18, st17,  computeP3(g->at(B11)->getPoint(), g->at(B21)->getPoint())));
        B19 =  g->add(new Node(14, npb19, st18,  computeP4(g->at(B11)->getPoint(), g->at(B21)->getPoint())));
        B20 =  g->add(new Node(8,  npb20, st19,  computeP5(g->at(B11)->getPoint(), g->at(B21)->getPoint())));
        
        // Segment between <0,-2,0> and <0,3,0>
        B22 =  g->add(new Node(1,  npb22, st21,  computeP2(g->at(B16)->getPoint(), g->at(B21)->getPoint())));
        B23 =  g->add(new Node(17, npb23, st22,  computeP3(g->at(B16)->getPoint(), g->at(B21)->getPoint())));
        B24 =  g->add(new Node(12, npb24, st23,  computeP4(g->at(B16)->getPoint(), g->at(B21)->getPoint())));
        B25 =  g->add(new Node(9,  npb25, st24,  computeP5(g->at(B16)->getPoint(), g->at(B21)->getPoint())));
        
        // Segment between <0,3,0> and <1,0,0>
        B26 =  g->add(new Node(11, npb26, st25,  computeP2(g->at(B21)->getPoint(), g->at(e)->getPoint())));
        B27 =  g->add(new Node(27, npb27, st26,  computeP3(g->at(B21)->getPoint(), g->at(e)->getPoint())));
        B28 =  g->add(new Node(28, npb28, st27,  computeP4(g->at(B21)->getPoint(), g->at(e)->getPoint())));
        B29 =  g->add(new Node(29, npb29, st28,  computeP5(g->at(B21)->getPoint(), g->at(e)->getPoint())));
        
        // Links the nodes in the graph.
        g->addLink(s, B2);
        g->addLink(B2, B3);
        g->addLink(B2, B4);
        g->addLink(B3, B5);
        g->addLink(B4, B5);
        g->addLink(B5, B6);
        g->addLink(B6, B7);
        g->addLink(B7, B8);
        g->addLink(B7, B9);
        g->addLink(B8, B10);
        g->addLink(B9, B10);
        g->addLink(B10, B11);
        g->addLink(B6, B12);
        g->addLink(B12, B13);
        g->addLink(B12, B14);
        g->addLink(B13, B15);
        g->addLink(B14, B15);
        g->addLink(B15, B16);
        g->addLink(B11, B17);
        g->addLink(B17, B18);
        g->addLink(B17, B19);
        g->addLink(B18, B20);
        g->addLink(B19, B20);
        g->addLink(B20, B21);
        g->addLink(B16, B22);
        g->addLink(B22, B23);
        g->addLink(B22, B24);
        g->addLink(B23, B25);
        g->addLink(B24, B25);
        g->addLink(B25, B21);
        g->addLink(B21, B26);
        g->addLink(B26, B27);
        g->addLink(B26, B28);
        g->addLink(B27, B29);
        g->addLink(B28, B29);
        g->addLink(B29, e);
        
    }
    
    
    
}

// Goes through and creates the other parts of the fractal until the level is 3.
// once the level is 3, the graph, boolean value, and the 2 indexes at that
// relative area are then sent to buildLevel3.
void buildGraph(Graph *g, bool p, int s, int e, int level) {
    int w, x, y, z;
    
    if (level == 3) {
        buildLevel3(g, p, s, e);
        return;
    } 
    
    if (level == 4) {
        w = 1;
        x = 2;
        y = -2;
        z = 3;
    } else {
        w = 0;
        x = 0; 
        y = 0;
        z = 0;
    }
    
    int a, b, c, d;
    
    int st1[] = {w,0,0, INT_MAX}, st2[] = {x,0,0, INT_MAX}, 
        st3[] = {y,0,0, INT_MAX}, st4[] = {z,0,0, INT_MAX}; 
    
    int np1[] = {s, b, c, INT_MAX}, np2[] = {a, d, INT_MAX}, 
        np3[] = {a, d, INT_MAX}, np4[] = {b, c, e, INT_MAX};
    
    a = g->add(new Node(31, np1, st1, computeP2(g->at(s)->getPoint(), g->at(e)->getPoint()) ));
    b = g->add(new Node(31, np2, st2, computeP3(g->at(s)->getPoint(), g->at(e)->getPoint()) ));
    c = g->add(new Node(31, np3, st3, computeP4(g->at(s)->getPoint(), g->at(e)->getPoint()) ));
    d = g->add(new Node(31, np4, st4, computeP5(g->at(s)->getPoint(), g->at(e)->getPoint()) )); 

    buildGraph(g, !p, s, a, level -1);
    buildGraph(g, !p, a, b, level -1);
    buildGraph(g, p, a, c, level -1);
    buildGraph(g, !p, b, d, level -1);
    buildGraph(g, p, c, d, level -1);
    buildGraph(g, !p, d, e, level -1);
}

// Takes the graph and initializes the starting points.
// After that, the two indexes, level, graph, and true are passed onto buildGraph
// So that the rest of the fractal can be created.
void buildInitialGraph(Graph *g, int level) {
    int s, e;
    int st1[] = {0, 0, 0, INT_MAX}, st2[] = {1, 0, 0, INT_MAX};
    int np1[] = {e, INT_MAX}, np2[] = {s, INT_MAX};
   
    Point pStart(0, 250);
    Point pEnd(1000, 250);
    
    s = g->add(new Node(31, np1, st1, pStart));
    e = g->add(new Node(31, np2, st2, pEnd));
    
    while (g->at(s)->sizeList() < level) {
        g->at(s)->pushListBack(0);
        g->at(e)->pushListBack(0);
    }
    
    bool p = true;
    buildGraph(g, p, s, e, level);
}


// Create 
int main() {
    Graph *g = new Graph();
    int level;

    //Point pStart(0, 250);
    //Point pEnd(1000, 250);
    //int s, e;
    
    //Node *n1 = new Node(pStart);
    //Node *n2 = new Node(pEnd);

    cout << "How many levels? ";
    cin >> level;
    
    buildInitialGraph(g, level);
    
    //createMetricSpace(n1, n2, level, g);
    //cout << "Done creating, size: " << g->size() << endl;

    //colorAllNodes(g, 10, level);
        
    g->xmlNodes();
    
    //cout << endl << "Highest Color: " << maxColorsUsed << endl;
    
    return 0;
}