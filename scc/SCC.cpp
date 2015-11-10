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
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef set<int>::iterator SetIt;  // aliasing the multiset iterator type used
typedef map<int, set<int> >::iterator MapIt;  // aliasing the map iterator type used
typedef list<int>::reverse_iterator ListIt;  // aliasing the list *reverse* iterator type used

/* Function prototypes */

string promptUserForFile(ifstream & infile, string prompt);
bool testFileName(ifstream & infile, string filename);
void readFile(map<int, set<int> > & graph, map<int, set<int> > & rgraph, ifstream & infile);
void print(map<int, set<int> > & mymap);
void print_size(map<int, set<int> > & mymap);
void print_biggest(map<int, set<int> > & scc);

void dfsloop(map<int, set<int> > & graph, list<int> & nodelist, map<int, set<int> > & scc, bool firstpass);
void dfs(map<int, set<int> > & graph, int explored[], int node, int leader, list<int> & nodelist, map<int, set<int> > & scc);

/* Main program */

using namespace std;

int main(int argc, char* argv[]) {
  map<int, set<int> > graph, rgraph;
  map<int, set<int> > scc;
  list<int> nodelist;
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
  readFile(graph, rgraph, infile);

  dfsloop(rgraph, nodelist, scc, true);
  dfsloop(graph, nodelist, scc, false);

  print_biggest(scc);

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
 */
void dfsloop(map<int, set<int> > & graph, list<int> & nodelist, map<int, set<int> > & scc, bool firstpass) {
  int max_node = (--graph.end()) -> first;
  int explored[max_node + 1];
  memset(explored, 0, sizeof explored);
  if (firstpass) {
    for (MapIt it = graph.begin(); it != graph.end(); ++it) {
      if (!explored[it -> first]) {
	dfs(graph, explored, it -> first, 0, nodelist, scc);
      }
    }
  } else {
    for (ListIt rit = nodelist.rbegin(); rit != nodelist.rend(); ++rit) {
      if (!explored[*rit]) {
	dfs(graph, explored, *rit, *rit, nodelist, scc);
      }
    }
  }
}

/*
 * Function: dfs
 * ------------------
 */
void dfs(map<int, set<int> > & graph, int explored[], int node, int leader, list<int> & nodelist, map<int, set<int> > & scc) {
  explored[node] = 1;
  if (leader != 0) {
    scc[leader].insert(node);
  }
  for (SetIt it = graph[node].begin(); it != graph[node].end(); ++it) {
    if (!explored[*it]) {
      dfs(graph, explored, *it, leader, nodelist, scc);
    }
  }
  nodelist.push_back(node);
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
void readFile(map<int, set<int> > & graph, map<int, set<int> > & rgraph, ifstream & infile) {
  int source_node, target_node;
  string line;
  while (getline(infile, line)) {
    istringstream stream(line);
    stream >> source_node; // 1st entry is the node number
    while(stream >> target_node) { // second entry is the target node
      graph[source_node].insert(target_node);
      rgraph[target_node].insert(source_node);
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

void print_size(map<int, set<int> > & mymap) {
  for (MapIt it = mymap.begin(); it != mymap.end(); ++it) {
    cout << it->first << " => " << (it -> second).size() << endl;
  }
}

void print_biggest(map<int, set<int> > & scc) {
  vector<int> mvector;
  for (MapIt it = scc.begin(); it != scc.end(); ++it) {
    mvector.push_back(it -> second.size());
  }
  sort(mvector.begin(), mvector.end());
  for (int i = 0; i < 5; i++) {
    if (!mvector.empty()) {
      cout << mvector.back() << ",";
      mvector.pop_back();
    } else {
      cout << 0 << ",";
    }
  }
  cout << endl;
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
