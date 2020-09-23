
//
// Created by marcela gomez on 2019-07-24.
// References Carrano Chp 20, geeksforgeeks Tutorial
//
#include <iomanip>
#include <fstream>
#include <iostream>
#include "graphl.h"


//==============================================================
//default constructor: initialized graph to size 0 with a
// GraphNode initialized to nullptr. (an array of lists)
//==============================================================
GraphL::GraphL() {
    sizeOfArray = 0;
    for (int i = 0; i < MAXNODES; i++) {
        graphArray[i].edgeHead = nullptr;
        graphArray[i].data = new NodeData();
        graphArray[i].visited = false;
    }
}


//==============================================================
//destructor: deletes node data, helper function used to access
// private data members below
//==============================================================
GraphL::~GraphL()
{
    makeEmpty();
}


//==============================================================
//buids up graph node information and adjacency list of edges
//between each node reading from a data file.
//reserve function of this to bring in data
//==============================================================
void GraphL::buildGraph(ifstream& infile)
{
    int fromNode = 0, toNode = 0;

    infile >> sizeOfArray;

    string Location;
    getline(infile, Location);
    //for # of locations, read in one line and set to data
    //end of file condition addressed in setData(infile)
    for (int i = 1; i < sizeOfArray +1 ; i++)
    {
        graphArray[i].data->setData(infile);
        cout << "node named: " << *graphArray[i].data << endl;
    }


    //following line is list of node edges and cost
    //each line consists of 3 integers representing an edge
    //fromNode = 0 means end of data for that graph
    while (infile >> fromNode >> toNode) {

        if (fromNode == 0 && toNode == 0) {
            break;
        } else {
            //helper function used to access private data
            cout << fromNode << "  " << toNode << endl;
            insertEdgeNode(fromNode, toNode);
        }
    }

    //graphArray = new GraphNode[sizeOfArray + 1];

}

//==============================================================
//Adjacency List constructed here by adding edges to
//corresponding nodes in the array of Nodes
//==============================================================
bool GraphL::insertEdgeNode(int fromNode, int toNode) {
    //check incoming vertices are in range
    if (fromNode > 0 && fromNode < MAXNODES && toNode > 0 && toNode < MAXNODES) {

        //create a new edge
        EdgeNode *newEdgeNode = new EdgeNode;
        //point NEN's next to the head of graphArray
        newEdgeNode->nextEdge = graphArray[fromNode].edgeHead;
        //put toNode as the adjGraphNode
        newEdgeNode->adjGraphNode = toNode;
        //move edgeHead to next insertion point newEdgeNode
        graphArray[fromNode].edgeHead = newEdgeNode;
        return true;
    }
    return false;
}


    //****code grave holding****
/*graphArray[i].data = new NodeData;
    graphArray[i].data->setData(Location);
    graphArray[i].visited = false;
    graphArray[i].edgeHead = nullptr;
    adjGraphNode = new GraphNode[sizeOfArray + 1];


    newEdgeNode->adjGraphNode = toNode;
    if (adjGraphNode[fromNode].edgeHead == nullptr) {
        newEdgeNode->nextEdge = nullptr;
        adjGraphNode[fromNode].edgeHead = newEdgeNode;
    } else {
        adjGraphNode[fromNode].edgeHead = newEdgeNode;
    }*/



//==============================================================
//Displays each node information and edge in the graph
//==============================================================
void GraphL::displayGraph()
{
    cout << "Graph: " << endl;
    for(int i = 1; i <= sizeOfArray; i++)
    {
        cout << "Node" << i << '\t';
        cout << '\t' << *graphArray[i].data << endl << endl;

        EdgeNode *temp = graphArray[i].edgeHead;
        while(temp != nullptr)
        {
            cout << " edge  " << i << "  " << temp->adjGraphNode << endl;
            temp = temp->nextEdge;
        }
    }

}


//==============================================================
//Makes a depth-first search and displays each node in depth-first
//order. Adapted from pseudocode in lecture as follows:
//
// dfs(v: vertex)
//  Mark v as visited
//  for ( each unvisited vertex u adjacent to v)
//      call dfs(u)
//==============================================================
void GraphL::depthFirstSearch()
{
    //mark all not visited
    for(int i = 1; i < sizeOfArray; i++){
        graphArray[i].visited = false;
    }

    cout << "Depth-first ordering: " ;

    for (int v = 1; v < sizeOfArray; v++){
        if(!graphArray[v].visited){
            dfs(v);
        }
    }
    cout << endl << endl;
}


//==============================================================
//dfs as adapted from lecture pseudocode as follows:
//
//v = visited; mark v as visited
//  do whatever with V;
//      for( w != visited){
//          dfs(w);
//}
//==============================================================
void GraphL::dfs(int v)
{
    graphArray[v].visited = true;  //v = visited; mark v as visited
    cout << v << " ";

    EdgeNode* tempPtr = graphArray[v].edgeHead;

    while (tempPtr != nullptr){

        if(!graphArray[tempPtr->adjGraphNode].visited){
            dfs(tempPtr->adjGraphNode);
        }
        tempPtr = tempPtr -> nextEdge;
    }
}


//==============================================================
//Helper function for destructor allows for access to private
//data members to delete nodes and node data.
//==============================================================
void GraphL::makeEmpty()
{
    if(sizeOfArray > 0 )
    {
        for (int i = 1; i < sizeOfArray + 1; i++)
        {
            while (graphArray[i].edgeHead != nullptr)
            {
                EdgeNode *current;
                current = graphArray[i].edgeHead;
                EdgeNode *nextNode;

                while (current != nullptr)             //not at end yet, cont.
                {
                    nextNode = current->nextEdge;       //advance pointer
                    delete current;                     //delete current
                    current = nextNode;                 //put next node at current
                }
                graphArray[i].edgeHead = nullptr;
            }
        }
        for (int i = 0; i < MAXNODES; i++)              //delete node data
        {
            delete graphArray[i].data;
            graphArray[i].data = nullptr;
        }
    }
}
