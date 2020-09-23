//
// Created by marcela gomez on 2019-07-24.
//
#include "graphm.h"


//=======================constructor===========================
// default
//TableType T[MAXNODES][MAXNODES]; --> stores visited, distance, path
//data member T is initialized to sets all dist to infinity,
// all visited to false, and all path to 0
//int C[MAXNODES][MAXNODES];  --> Cost array, the adjacency matrix
//==============================================================
GraphM::GraphM()
{
    //int size = 0;
    //int INT_MAX = INFINITY;
    for(int i = 1; i < MAX_NODES; ++i)
    {
        for(int j = 1; j < MAX_NODES; j++)
        {
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
            C[i][j] = INT_MAX;
        }
    }
}


//=====================buildGraph===============================
// builds up graph node information and adjacency matrix of edges
// between each node reading from a data file.
//==============================================================
void GraphM::buildGraph(ifstream& input) {

    int nodes = 0;
    int start = 0, end = 0, cost = 0;
    string Location;

    input >> nodes;                      //read in size
    //cout << "size: " << size << endl;

    if (nodes > 0 && nodes < MAX_NODES)
    {

        getline(input, Location);
        size = nodes;//get location names

        for (int i = 1; i <= size; ++i)
        {
            data[i].setData(input);
            //C[i][i] = 0;
        }//set data for each

        input >> start >> end >> cost;

        while (start != 0) {

            input.get();
            insertEdge(start, end, cost);
            if (!input.get())
              break;
            if (input.eof())
                break;
            input >> start >> end >> cost;
        }

    }
}


//=========================insertEdge=========================
// insert an edge into graph between two given nodes
//==============================================================
bool GraphM::insertEdge(int s, int e, int c)
{
    //s-> start, e-> end, c->cost
    if(s > 0 && e > 0 && c > 0 && s <= size && e <= size ){
        C[s][e] = c;
        return true;
        //cout << "edge: " << "start " << s << "  end " << e << "  cost " << c << endl;
    }
    return false;
}


//======================removeEdge===============================
//  remove an edge between two given nodes
//==============================================================
bool GraphM::removeEdge(int start, int end)
{
    C[start][end] = INT_MAX;
    return true;
}


//===========================findShortestPath=======================
// shortest path between every node to every other node in the graph
//Pseudocode as follows
//Set all vertices dist to infinity, set source to dist 0
//Mark source visited and find smallest vertex v
//for each w adj to v make comparison of smallest path
// for int k = i k <= n k ++
//      for i = 1 i <= n, i++
//          for j = 1 j <= n j++
//              dist[i][j] = min(dist[i][j], dist[i][k] + kist [k][j])
//==============================================================
void GraphM::findShortestPath()
{

    for(int source = 1; source <= size; source++) {
        //starting distance is 0, mark visited
        T[source][source].dist = 0;
        T[source][source].visited = true;

        // retrieve distances for neighbor nodes from C
        for (int i = 1; i <= size; i++)
        {
            if (C[source][i] != INT_MAX) {
                T[source][i].dist = C[source][i];
                T[source][i].path = source;
            }
        }
        int v = 0;

        do
        {
            //finds smallest distance from neighbors to get v
            v = 0;
            int minDist = INT_MAX;
            for (int j = 1; j <= size; j++) {

                if (!T[source][j].visited && C[source][j] < minDist)
                {

                    minDist = C[source][j];
                    v = j;
                }
            }
            if(v == 0)
            {
                break;
            }
            T[source][v].visited = true;    //mark smallest v visited


            for (int w = 1; w <= size; w++)
            {
                if (!T[source][w].visited && C[v][w] != INT_MAX)    //consider not visited and not infinity
                {
                    if(v != w)      //no check if equal
                    {
                        //get min of dist or previous v + C
                        T[source][w].dist = min(T[source][w].dist, T[source][v].dist + C[v][w]);

                        //return the smaller v of the two to update path
                        //won't update without additonal comparison here, going to wrong node
                        if(T[source][w].dist < T[source][v].dist + C[v][w] )
                        {
                            T[source][w].path = T[source][w].path;
                        }
                        else
                        T[source][w].path = v;
                    }
                }
            }
        }while (v != 0);        //keep going until arriving at source
    }
}


//==========================displayAll==========================
// Displays shortest path from v to all other neighboring nodes
//==============================================================
void GraphM::displayAll()
{
    //set headings
    cout << "Description\t\t " << "From Node\t" << "To Node  \t";
    cout << "Dijkstra's\t\t" << "Path" << endl;

    //use cout to print edge, dist & path data
    for (int i = 1; i < size + 1; i++)
    {
        cout << data[i] << endl << endl;

        for(int j = 1 ; j <= size; ++j)
        {

            if (i != j)
            {                //T[i][j].dist != 0

                cout << setw(25) << i << "\t\t\t" << j;

                if (T[i][j].dist != INT_MAX)
                {
                    cout << setw(10) << T[i][j].dist << "              ";
                }

                else {
                    cout << "        ----";
                    //break;
                }
                getPath(i, j);
                cout << endl;
            }

        }
    }
}


//=============================display==========================
// Displays path between two vertices
//==============================================================
void GraphM::display(int start, int end)
{
    //catch all possible error's for non existent edges
    if(start > size || start < 0 || end > size || size < 0 || T[start][end].dist == INT_MAX)
    {
        cout << "\t" << start << "\t\t" << end;
        cout << "\t\t" << "-----" << endl;
        return;
    }


    if(start > 0 && end > 0 && start <= size && end <= size)
    {
        //cout << "Debug: start " << start << ", end " << end << ", location " << data[T[start][end].path] << endl;

        if (T[start][end].dist != INT_MAX)
        {
            cout << "\t" <<start << "\t\t" << end << "\t\t";
            cout << T[start][end].dist << "     ";
            getPath(start, end);
            cout << endl;
            //getPath(start, end);
        }
    }
    getLocations(start,end);
    cout << endl;
}


//==========================getPath=============================
// Helper function for display to help retrieve path vertices
//==============================================================
void GraphM::getPath(int start, int end) {

    if(T[start][end].dist == INT_MAX)
    {
        return;
    }

    if(start == end)
    {
        cout << end << " ";
        return;
    }

    if (start != end) {

        int nodeTrace = end;
        if (T[start][end].path != 0) {
            getPath(start, nodeTrace = T[start][end].path);

        }
    }
    cout << end << " ";

}


//=========================getLocations=========================
// Helper function retrieves location data for each vertice
//==============================================================
void GraphM::getLocations(int start, int end)
{
    if(T[start][end].dist == INT_MAX)
    {
        cout << "";
    }
    else
    {
        if(start == end)
        {
            cout << data[start] <<endl;
            return;
        }
        int v = end;
        getLocations(start, T[start][end].path);
        cout << data[v] << endl;
    }
}
