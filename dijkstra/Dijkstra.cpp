/*
 * File: Dijkstra.cpp
 * -----------------------
 * This program is an implementation of the Dijkstra shortest path
 * algorithm to find all shortest paths between a source vertex
 * and all other vertices in a graph.
 * It reads an undirected graph from a file cotaining an
 * adjacency list representation of an undirected weighted graph.
 * Each row consists of the node tuples that are adjacent to that particular vertex
 * along with the length of that edge. For example, the 6th row has 6 as the first entry
 * indicating that this row corresponds to the vertex labeled 6.
 * The next entry of this row "141,8200" indicates that there is an edge between
 * vertex 6 and vertex 141 that has length 8200.
 * The rest of the pairs of this row indicate the other vertices adjacent to vertex 6
 * and the lengths of the corresponding edges.
 * The first argument of the program must be the source vertex (number).
 * The graph file can be specified as the first argument of the program,
 * or it will be prompted for by the program.
 * The priogram writes the result to std output. It outputs the vertices
 * and the shortest path distances to these vertices.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <utility> // std::pair
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef vector<int>::iterator VecIterator;  // aliasing the vector iterator type used
typedef set<pair <int, int> >::iterator SetIterator;  // aliasing the set iterator type used
typedef set<int>::iterator SetIntIterator;  // aliasing the set iterator type used
typedef map<int, set<pair <int, int> > >::iterator MapIterator;  // aliasing the map iterator type used

/* Function prototypes */

string promptUserForFile(ifstream & infile, string prompt);
bool testFileName(ifstream & infile, string filename);
void readFile(map<int, set<pair<int, int> > > & graph, ifstream & infile);
void print(map<int, set<pair<int, int> > > & graph);
int stringToInteger(string str);

void mainloop(map<int, set<pair<int, int> > > & graph, set<int> & processed, int distances[]);

int sourceNode, maxNodes;
const int MAX_DIST = 1000000;

/* Main program */

using namespace std;

int main(int argc, char* argv[]) {

  ifstream infile;

  if (argc < 3) {
    cerr << "Invalid number of arguments\n"
	 <<"Usage: " << argv[0] << " SOURCE_NODE MAX_NODES [FILENAME]" << endl;
    return 1;
  } else {
    sourceNode = stringToInteger(argv[1]);
    maxNodes = stringToInteger(argv[2]);
  }
  if (argc < 4) {
    promptUserForFile(infile, "Input file: ");
  }
  else {
    if (!testFileName(infile, argv[3])) {
      cerr << "No such file\n"
	   <<"Usage: " << argv[0] << " FILENAME" << endl;
      return 1;
    }
  }
  cout << "start: " << sourceNode << " max nodes: " << maxNodes << endl;

  map<int, set<pair<int, int> > > graph;
  readFile(graph, infile);

  set<int> processed; // vertices processed so far
  processed.insert(sourceNode);  

  int distances[maxNodes]; // computed shortest path distances
  memset(distances, MAX_DIST, sizeof distances); // set all distances to max

  distances[sourceNode] = 0; // set distance to source node equal to zero

  // lets start
  mainloop(graph, processed, distances);

  print(graph);

  return 0;
}

/*
 * Function: mainloop
 * -------------------
 * This function loops processes one node at a time
 * according to Dijkstra's greedy criterion,
 * adding the processed node to the processed array
 * until there are no more nodes to process.
 */
void mainloop(map<int, set<pair<int, int> > > & graph, set<int> & processed, int distances[]) {
  int graph_size = graph.size();
  for (int i = 1; i < graph_size; i++) {
    for (SetIntIterator it = processed.begin(); it != processed.end(); ++it) {
  
    }
  }
}

/*
 * Function: readFile
 * Usage: map<int, vector<int> > graph; readFile(graph);
 * --------------------------------------
 * Asks for a file with directed edges of a graph and reads the numbers into a
 * data structure consisting of a map with one key for each vertex. The keys
 * of the map each points to a vector. The indexes of the vecor represent the vertices
 * to which the key veriex has outgoing edges. The value at a particular index
 * is the edge length. A value of -1 indicates that there is no edge.
 */
void readFile(map<int, set<pair<int, int> > > & graph, ifstream & infile) {
  int current_node, target_node, edge_length;  
  string target_edge;
  string line; // a complete row of the file
  int di; // delimiter index
  while (getline(infile, line)) {
    istringstream stream(line);
    stream >> current_node; // 1st entry is the node number
    set<pair<int, int> > row;
    while(stream >> target_edge) { // target nodes with edge lengths
      di = target_edge.find(",");
      target_node = stringToInteger(target_edge.substr(0, di));
      edge_length = stringToInteger(target_edge.substr(di + 1));
      if (target_node <= maxNodes) {
	row.insert(make_pair(target_node, edge_length));
	// row[target_node - 1] = edge_length;
      } else {
	cout << "Warning: node number exceeded max nodes" << endl;
      }
    }
    if (current_node <= maxNodes) {
      graph[current_node] = row;
    } else {
      cout << "Warning: node number exceeded max nodes" << endl;
    }
  }
  infile.close();
}

/*
 * Function: print
 * Usage: vector<int> vec; print(vec);
 * ------------------------------------
 * Prints the content of a vector, one item per 
 */
void print(map<int, set<pair<int, int> > > & graph) {
  set<pair <int, int> > mvector;
  for (MapIterator it = graph.begin(); it != graph.end(); ++it) {
    mvector = it -> second;
    cout << it -> first << " => ";
    for (SetIterator it2 = mvector.begin(); it2 != mvector.end(); ++it2) {
      cout << "(" << it2 -> first << ", " << it2 -> second << ")" << ", ";
    }
    cout << endl;
  }
}

/*
 * Function: promptUserForFile
 * Usage: string filename = promptUserForFile(infile, prompt);
 * -----------------------------------------------------------
 * Asks the user for the name of an input file and opens the reference
 * parameter infile using that name, which is returned as the result of
 * the function. If the requested file does not exist, the user is
 * given additional chances to enter a valid file name. The optional
 * prompt argument is used to give the user more information about the
 * desired input file.
 */
string promptUserForFile(ifstream & infile, string prompt) {
  while (true) {
    cout << prompt;
    string filename;
    getline(cin, filename);
    if (testFileName(infile, filename)) return filename;
    infile.clear();
    cout << "Unable to open that file. Try again." << endl;
    if (prompt == "") prompt = "Input file: ";
  }
}

bool testFileName(ifstream & infile, string filename) {
  infile.open(filename.c_str());
  return !infile.fail();
}

int stringToInteger(string str) {
  istringstream stream(str);
  int value;
  stream >> value >> ws;
  if (stream.fail() || !stream.eof()) {
    cerr << "stringToInteger: Illegal integer format (" + str + ")";
    return 1;
  }
  return value;
}
