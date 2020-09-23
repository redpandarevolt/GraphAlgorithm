//
// Created by marcela gomez on 2019-07-24.
//

#include <iostream>
#include <fstream>
#include "graphl.h"
#include "graphm.h"

using namespace std;



int main ()
{
    //Program 3 - Part One Dijkstra's shortest path algorithm
    cout << "Open file using ifstream" << endl << endl;

    //******REMOVE FILE PATH BEFORE SUBMITTING*************
    ifstream infile1("data31.txt");
    if(!infile1)
    {
        cout << "Error: file did not open." << endl;
        return -1;
    }
    cout << "First file Opened Successfully" << endl << endl;

    for (;;)
    {
        GraphM G;               //Build a Graph object
        G.buildGraph(infile1);  //configure G with data from file
        if (infile1.eof())
        {
            break;
        }
        //G.displayAll();
        G.findShortestPath();   //get shortest path from v to all other v's
        G.displayAll();
        G.display(3, 1);        // display path from node 3 to 1 to cout
        G.display(1, 2);
        G.display(1, 4);
        G.display(5, 2);
        G.display(4, 3);
        G.display(5, 4);
    }
    infile1.close();


    //Program 3 - part 2 dfs using adj list
    cout << "Open second file using ifstream" << endl;
    ifstream infile2("data32.txt");
    if(!infile2)
    {
        cout << "Error: file did not open." << endl;
        return 1;
    }
    cout << "Second File Opened Successfully" << endl;

    for (;;)
    {
        GraphL G;
        G.buildGraph(infile2);
        if (infile2.eof())
        {
            break;
        }
        G.displayGraph();
        G.depthFirstSearch();
    }
    infile2.close();

}