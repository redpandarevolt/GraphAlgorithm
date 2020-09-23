//
// Created by marcela gomez on 2019-07-24.
//

#ifndef GRAPHS_GRAPHM_H
#define GRAPHS_GRAPHM_H

#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>
#include <iomanip>
#include "nodedata.h"
using namespace std;
#define INFINITY INT_MAX


const int MAX_NODES = 101; //


struct TableType    //table struct to hold shortest pahts
{
    bool visited;
    int dist;
    int path;
};


class GraphM {

public:


    GraphM();                           //constructor
    void buildGraph(ifstream& input);   //build graph from data in file
    bool insertEdge(int s, int e, int c);//insert edge from the file data
    bool removeEdge(int , int);         //remove edge by reseting to infinity
    void findShortestPath();            //Dijsktra's shortest path
    void displayAll();                  //display's Dijkstra's outcome
    void display(int start, int end);   // display on path
    void getPath(int start, int end);   //helper function to displays
    void getLocations(int start, int end);  //helper func retrieves data


private:

    NodeData data[MAX_NODES];            // data for graph nodes
    int C[MAX_NODES][MAX_NODES];          // adjacency matrix
    int size;                           //number of nodes in graph
    TableType T [MAX_NODES][MAX_NODES];   //stores visited, distance, path

};

#endif //GRAPHS_GRAPHM_H
