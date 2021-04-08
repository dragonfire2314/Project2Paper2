/**
 *  @author https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
 *  @author Modified by. Tanner Kern
 *  @file primNoSTL.cpp
 *  @brief This file takes in a text file that contains a list of vertices and there edges and runs Prims algorithm on it. This file does not use the STL datastructures to achive this
 * 
*/

#include <fstream>
#include <chrono>
#include <string>
#include <iostream>

#include "myLib.h"
#include "demo.h"

using namespace std;

#define INT_MAX 2147483647
// STL implementation of Prim's algorithm for MST
# define INF 0x3f3f3f3f
  
// iPair ==> Integer Pair
typedef pair<int, int> iPair;
 
/**
 * T_make_pair - makes a pair
 *
 * @param i1 first element
 * @param i2 second element
 */
Pair T_make_pair(int i1, int i2) {
    Pair p;
    p.first = i1;
    p.second = i2;

    return p;
}

// To add an edge
/**
 * addEdge - adds an edge to the adjacency list
 *
 * @param adj the adjacency list
 * @param u the first edge
 * @param v the second edge
 * @param wt the weight
 */
void addEdge(TVector_pair adj[], int u,
                                     int v, int wt)
{
    adj[u].push_back(T_make_pair(v, wt));
    adj[v].push_back(T_make_pair(u, wt));
}
 
// Prints shortest paths from src to all other vertices
/**
 * addEdge - adds an edge to the adjacency list
 *
 * @param adj the adjacency list
 * @param V the size of the adjacency list
 * @param m a map that contains to vertices name mapping
 */
void primMST(TVector_pair adj[], int V, Map_Str_Int m, int starting)
{
    auto start = std::chrono::high_resolution_clock::now();
    // Create a priority queue to store vertices that
    // are being preinMST. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
    //priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    //HeapADT<Pair> heap;
    priorityQueue<Pair> pq;
 
    int src = starting; // Taking vertex 0 as source
 
    // Create a vector for keys and initialize all
    // keys as infinite (INF)
    TVector<int> key(V, INF);
 
    // To store parent array which in turn store MST
    TVector<int> parent(V, -1);
 
    // To keep track of vertices included in MST
    TVector<bool> inMST(V, false);
 
    // Insert source itself in priority queue and initialize
    // its key as 0.
    pq.push(T_make_pair(0, src));
    key.set(src, 0);
 
    /* Looping till priority queue becomes empty */
    while (!pq.empty())
    {
        //printf("Pass: %d, %d\n", pq.top().first, pq.top().second);
        // The first vertex in pair is the minimum key
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted key (key must be first item
        // in pair)

        int u = pq.top().second;
        pq.pop();
 
        inMST.set(u, true); // Include vertex in MST
 
        // Traverse all adjacent of u
        //for (auto x : adj[u])
        for (int i = 0; i < adj[u].size(); i++)
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = adj[u][i].first;
            int weight = adj[u][i].second;
 
            // If v is not in MST and weight of (u,v) is smaller
            // than current key of v
            if (inMST[v] == false && key[v] > weight)
            {
                // Updating key of v
                key.set(v, weight);
                //printf("Add: %d, %d\n", key[v], v);
                pq.push(T_make_pair(key[v], v));
                parent.set(v, u);
            }
        }
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
 
    // Print edges of MST using parent array
    for (int i = 1; i < V; ++i)
        printf("%s - %s\n", m.getIndexFromInt(parent[i]).c_str(), m.getIndexFromInt(i).c_str());

    printf("Time elapsed: %d microseconds\n", microseconds);
}
 
// Driver program to test methods of graph class
int main(int argc, char* argv[])
{
    if (argc != 5) {
        printf("Invalid arguments, please use the form ./a.out <filename> <number of vertices> <maximum edge cost> <random seed>\n");
        return 0;
    }

    TVector_pair* adj;

    Map_Str_Int map;

    std::ifstream file(argv[1]);
    if (file.is_open())
    {
        int amountOfVertices, amountOfEdges;
        std::string line, line2, line3;
        //Get in the amount
        file >> amountOfVertices; //Amount
        //Create the adjacent list
        adj = new TVector_pair[amountOfVertices];
        //Take in all of the vertices
        int counter = 0;
        int c1, c2, c3;
        while (file >> line >> line2 >> line3)
        {
            if (map.isInMap(line)) {
                c1 = map[line];
            } else {
                map.addToMap(line, counter);
                c1 = counter;
                counter++;
            }

            if (map.isInMap(line2)) {
                c2 = map[line2];
            } else {
                map.addToMap(line2, counter);
                c2 = counter;
                counter++;
            }

            c3 = std::stoi(line3);

            //Add the vertices
            addEdge(adj, c1, c2, c3);
        }

        printf("Enter all starting vertices, to stop input -1.\n");
        TVector_str starts;
        while(true) {
            std::string str;
            cin >> str;
            if (str == "-1") break;
            starts.push_back(str);
        }
        
        for (int i = 0; i < starts.size(); i++) {
            //Run the prim algorithm
            printf("Run %d, starting vertex %s\n", i, starts[i].c_str());
            if (map.isInMap(starts[i].c_str()))
                primMST(adj, amountOfVertices, map, map[starts[i].c_str()]);
            else
                printf("Vertex was input wrong: %s\n", starts[i].c_str());
        }
    }

    //Close the file
    file.close();
 
    return 0;
}