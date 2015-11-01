/*
 * File: Contraction.cpp
 * -----------------------
 * This program is an implementation of the randomized contraction
 * algorithm to find the min-cut of a graph. It reads a graph in form
 * of an adjacency list from a file specified as the first argument of
 * the program, or prompted for, and writes the result to std output.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <stdlib.h>
#include <algorithm>
using namespace std;

typedef multiset<int>::iterator MSetIt;  // aliasing the multiset iterator type used
typedef map<int, multiset<int> >::iterator MapIt;  // aliasing the map iterator type used

/* Function prototypes */

string promptUserForFile(ifstream & infile, string prompt);
bool testFileName(ifstream & infile, string filename);
void readFile(map<int, multiset<int> > & mymap, ifstream & infile);
void print(map<int, multiset<int> > & mymap);

int mincut(map<int, multiset<int> > mymap);
int getRandomKey(map<int, multiset<int> > & mymap);
int getRandomElement(multiset<int> mset);
void contract(map<int, multiset<int> > & mymap, int node1, int node2);

/* Main program */

using namespace std;

int main(int argc, char* argv[]) {
  map<int, multiset<int> > in_graph;
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
  readFile(in_graph, infile);
  int n = in_graph.size();;
  int min_k = n;
  int k; // size of min-cut set
  srand(time(NULL));
  for (int i = 0; i < min(n * n, 200); i++) {
    k = mincut(in_graph);
    min_k = min(min_k, k);
    // cout << "i= " << i << " k= " << k << " min= " << min_k << endl;
  }
  // print(in_graph);
  cout << "Min-cut size: " << min_k << endl;
  return 0;
}

/*
 * Function: mincut
 * -------------------
 * This function performs the random contraction alorithm
 * due to karger and works as follows:
 * While there are more than 2 vertices
 * - pick a remaining edge (u,v) uniformly at random
 * - merge ("contract" ) u and v into a single vertex
 * - remove self-loops
 * return cut represented by final 2 vertices
 */
int mincut(map<int, multiset<int> > mymap) {
  while (mymap.size() > 2) {
    int node1 = getRandomKey(mymap);
    int node2 = getRandomElement(mymap[node1]);
    contract(mymap, node1, node2);
  }
  return mymap[getRandomKey(mymap)].size();
  }

int getRandomKey(map<int, multiset<int> > & mymap) {
  int r = rand() % mymap.size();
  MapIt it = mymap.begin();
  for (int i = 0; i < r; i++) it++;
  return it->first;
}

int getRandomElement(multiset<int> mset) {
  int r = rand() % mset.size();
  MSetIt it = mset.begin();
  for (int i = 0; i < r; i++) it++;
  return *it;
}

/*
 * Function: contract
 * ------------------
 * Contract 2 nodes (node1 and node2) from the graph (mymap).
 * node1 will remain, node2 will be deleted.
 * 1. iterate over all elements (edges) of node2 and exchange
 * all instances of node2 with node1 within the node sets indicated by
 * the elements in node2
 * 2. add all elements of the node2 set into the node1 set
 * 3. remove node2 from the graph (the respective key in the map)
 * 4. remove all occurrences of node1 and of node2 in the combined set
 */
void contract(map<int, multiset<int> > & mymap, int node1, int node2) {
  // part 1.
  multiset<int> node2set = mymap[node2];
  for (MSetIt it = node2set.begin(); it != node2set.end(); ++it) {
    pair<MSetIt, MSetIt> ret = mymap[*it].equal_range(node2); // mymap[*it] is the target node
    int n = mymap[*it].count(node2); // number of node2 elements we remove
    mymap[*it].erase(ret.first, ret.second);
    for (int i = 0; i < n; i++) mymap[*it].insert(node1); // add same number of node1 elements}
  }

  // part 2.
  for (MSetIt it = node2set.begin(); it != node2set.end(); ++it) {
    mymap[node1].insert(*it);
  }

  // part 3.
  mymap.erase(node2);

  // part 4.
  pair<MSetIt, MSetIt> ret = mymap[node1].equal_range(node1); // remove internal edges node1
  mymap[node1].erase(ret.first, ret.second);
  ret = mymap[node1].equal_range(node2); // remove internal edges node2
  mymap[node1].erase(ret.first, ret.second);
}

/*
 * Function: readFile
 * Usage: map<int, multiset> graph; readFile(graph);
 * --------------------------------------
 * Asks for a file with numbers and reads the numbers into the vector;
 */
void readFile(map<int, multiset<int> > & mymap, ifstream & infile) {
  int this_node;
  int other_node;
  string line;
  while (getline(infile, line)) {
    istringstream stream(line);
    stream >> this_node; // 1st entry is the node number
    multiset<int> mset;
    while(stream >> other_node) { // other enries are target nodes
      mset.insert(other_node);
    }
    mymap.insert(pair<int, multiset<int> >(this_node, mset));
  }
  infile.close();
}

/*
 * Function: print
 * Usage: vector<int> vec; print(vec);
 * ------------------------------------
 * Prints the content of a vector, one item per line.
 */
void print(map<int, multiset<int> > & mymap) {
  multiset<int> mset;
  for (MapIt it = mymap.begin(); it != mymap.end(); ++it) {
    mset = it->second;
    cout << it->first << " => ";
    for (MSetIt it2 = mset.begin(); it2 != mset.end(); ++it2) {
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
