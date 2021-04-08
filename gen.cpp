/// File: GraphGen.cpp
/// Quick and Dirty Generator of Graphs Represented by Adjacency Lists
/// Written by Dr. Spiegel
///
/// This program will generate a graph with the number of vertices and maximum cost 
///  (cost is positive and of type int) provided by the user.
///
/// The user will also provide a seed for the random number generator.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

const int MAXVERTICES=10;

// If fully connected, only thing random is cost of edges
void fullyConnected(ofstream &outFile,int vertices,int maxCost);

int main(int argc,char **argv)
{ if (argc != 5) {
    cerr << "Form: gen <data file>  |V| <max cost> <seed>\n";
    return(-1);
  }
  // Set up data file
  ofstream outFile;		// argv[1] is file name
  outFile.open(argv[1]);	// We assume success (recall: quick and dirty)
  int vertices=atoi(argv[2]),	// # vertices in graph
      maxCost=atoi(argv[3]),
      seed=atoi(argv[4]);

  srand(seed);			// Seed random number generator
  //   Let's write the file
  outFile << vertices << endl;
  // Check for fully connected
  fullyConnected(outFile,vertices,maxCost);
  outFile.close();		// Done  
  return(0);  
}    
    
// If fully connected, only thing random is cost of edges
void fullyConnected(ofstream &outFile,int vertices,int maxCost)
{ for (int vertex=1;vertex<=vertices;vertex++) 
//    for (int edge=1;edge<=vertices;edge++)
    for (int edge=vertex;edge<=vertices;edge++)
      if (edge != vertex)
        outFile << (char)(vertex+96) << " " << (char)(edge+96) << " " << rand() % maxCost + 1 << endl;
}	
