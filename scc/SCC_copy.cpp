/*
 * File: SCC.cpp
 * -----------------------
 * This program is an implementation of the Kosaraju's two-pass
 * algorithm to find the strongly connected components of a graph.
 * It reads a directed graph from a file with one edge per row where
 * the vertex label in first column is the tail and the vertex label
 * in second column is the head.
 * The file can be specified as the first argument of the program,
 * or it is prompted for.
 * The priogram writes the result to std output. It outputs the sizes
 * of the SCCs in the given graph, in decreasing order of sizes.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <list>
#include <stdlib.h>
#include <algorithm>
using namespace std;

typedef set<int>::iterator SetIt;  // aliasing the multiset iterator type used
typedef map<int, set<int> >::iterator MapIt;  // aliasing the map iterator type used
typedef list<int>::reverse_iterator ListIt;  // aliasing the list *reverse* iterator type used

/* Function prototypes */

string promptUserForFile(ifstream & infile, string prompt);
bool testFileName(ifstream & infile, string filename);
void readFile(map<int, set<int> > & mymap, ifstream & infile);
void print(map<int, set<int> > & mymap);

void dfsloop(map<int, set<int> > & mymap, list<int> & nodelist, list<int> & nodelist2, int f[], bool firstpass);
void dfs(map<int, set<int> > & mymap, bool explored[], int node, int f[], list<int> & nodelist2, bool firstpass);
void getReverseTargetNodes(map<int, set<int> > & mymap, int node, set<int> & targetNodes);

int t; // finishing times for first pass of dfs loop


/* Main program */

using namespace std;

int main(int argc, char* argv[]) {
  map<int, set<int> > ingraph;
  ifstream infile;
  if (argc < 2) {
    promptUserForFile(infile, "Input file: ");
  }
  else {
    if (!testFileName(infile, argv[1])) {
      cerr << "No such file\n"
	   <<"Usage: " << argv[0] << " FILENAME" << endl;
      return 1;
    }
  }
  readFile(ingraph, infile);
  int max_node = (--ingraph.end()) -> first;
  cout << "max node: " << max_node << endl;
  // int finishing_times[max_node + 1];
  list<int> nodelist;
  list<int> nodelist2;
  for (MapIt it = ingraph.begin(); it != ingraph.end(); ++it) {
    nodelist.push_back(it -> first);
  }
  dfsloop(ingraph, nodelist, nodelist2, NULL, true);
  print(ingraph);
  // cout << "finishing times: " << endl;
  // for (int i = 1; i <= max_node; i++) cout << finishing_times[i] << ", ";
  // cout << endl;
  cout << "node list reversed: " << endl;
  for (ListIt rit = nodelist2.rbegin(); rit != nodelist2.rend(); ++rit) cout << *rit << ", ";
  cout << endl;
  cout << "Results: " << endl;
  return 0;
}

/*
 * Function: dfsloop
 * -------------------
 * This function loops through all nodes and perfroms
 * dfs to identify source nodes and sccs respectively.
 * In a first pass, the dfs-loop is run on the reverse
 * graph to order the nodes for the actual ssc.
 * In a second pass the dfs-loop on the original graph
 * to find the sscs, thereby using the result of the first pass.
 *
 * mymap is the graph, f is an array with finishing times,
 * reverse is true if dfs should be done in reverse order
 *
 * Returns ...
 */
void dfsloop(map<int, set<int> > & mymap, list<int> & nodelist, list<int> & nodelist2, int f[], bool firstpass) {
  t = 0;
  int max_node = (--mymap.end()) -> first;
  bool explored[max_node + 1];
  if (firstpass) {
    for (ListIt rit = nodelist.rbegin(); rit != nodelist.rend(); ++rit) {
      if (!explored[*rit]) {
	dfs(mymap, explored, *rit, f, nodelist2, firstpass);
      }
    }
  } else {
    for (MapIt it = ingraph.begin(); it != ingraph.end(); ++it) {
      if (!explored[*rit]) {
	dfs(mymap, explored, *rit, f, nodelist2, firstpass);
      }
    }
  }
}

/*
 * Function: dfs
 * ------------------
 */
void dfs(map<int, set<int> > & mymap, bool explored[], int node, int f[], list<int> & nodelist2, bool firstpass) {
  explored[node] = true;
  set<int> targetNodes;
  if (firstpass) {
    getReverseTargetNodes(mymap, node, targetNodes);
  } else {
    targetNodes = mymap[node];
  }
  for (SetIt it = targetNodes.begin(); it != targetNodes.end(); ++it) {
    if (!explored[*it]) {
      dfs(mymap, explored, *it, f, nodelist2, reverse);
    }
  }
  t++;
  f[node] = t;
  nodelist2.push_back(node);
  cout << node << ": " << t << endl;;
}

void getReverseTargetNodes(map<int, set<int> > & mymap, int node, set<int> & targetNodes) {
  set<int> targetset;
  for (MapIt it = mymap.begin(); it != mymap.end(); ++it) {
    targetset = it -> second;
    if (targetset.count(node) != 0) {
      targetNodes.insert(it -> first);
    }
  }
}

/*
 * Function: readFile
 * Usage: map<int, multiset> graph; readFile(graph);
 * --------------------------------------
 * Asks for a file with directed edges of a graph and reads the numbers into a
 * data structure consisting of a map with one key for each vertex. The keys
 * of the map each points to a multiset. The elements of the multisets are the vertices
 * to which the key veriex has outgoing edges. 
 */
void readFile(map<int, set<int> > & mymap, ifstream & infile) {
  int source_node, target_node;
  string line;
  while (getline(infile, line)) {
    istringstream stream(line);
    stream >> source_node; // 1st entry is the node number
    while(stream >> target_node) { // second entry is the target node
      mymap[source_node].insert(target_node);
      // cout << source_node << ", " << target_node << endl;
    }
  }
  infile.close();
}

/*
 * Function: print
 * Usage: vector<int> vec; print(vec);
 * ------------------------------------
 * Prints the content of a vector, one item per line.
 */
void print(map<int, set<int> > & mymap) {
  set<int> mset;
  for (MapIt it = mymap.begin(); it != mymap.end(); ++it) {
    mset = it->second;
    cout << it->first << " => ";
    for (SetIt it2 = mset.begin(); it2 != mset.end(); ++it2) {
      cout << *it2 << ", ";
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
