//
// Created by marcela gomez on 2019-07-24.
//

#ifndef GRAPHS_GRAPHL_H
#define GRAPHS_GRAPHL_H

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include "nodedata.h"
using namespace std;


const int MAXNODES = 101;


struct EdgeNode;            //forward reference for compiler

struct GraphNode {          //structs used for simplicity, use classes if desired
    EdgeNode* edgeHead;     //head of the list of edges
    NodeData* data;         // data information about each node
    bool visited;
};

struct EdgeNode {
    int adjGraphNode;       // subscript of the adjacent graph node
    EdgeNode* nextEdge;
};


class GraphL {

public:

    //constructor and deconstructor
    GraphL();
    ~GraphL();

    //takes file data in and assigns to proper elements
    void buildGraph(ifstream& infile);

    //displays graph as constructed
    void displayGraph();

    //search dfs style for efficiency improvement over adj matrix
    void depthFirstSearch();


private:

    int sizeOfArray;
    GraphNode graphArray[MAXNODES];

    //Utility functions
    void dfs(int v);
    bool insertEdgeNode(int fromNode, int toNode);
    void makeEmpty();


};

#endif //GRAPHS_GRAPHL_H