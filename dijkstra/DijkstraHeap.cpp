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

typedef set<pair <int, int> >::iterator SetIterator;  // aliasing the set iterator type used
typedef set<int>::iterator SetIntIterator;  // aliasing the set with int iterator type used
typedef map<int, set<pair <int, int> > >::iterator MapIterator;  // aliasing the map iterator type used
typedef map<int, list<int> >::iterator MapListIterator;  // aliasing the map list iterator type used
typedef map<int, int>::iterator MapIntIterator;  // aliasing the map int iterator type used
typedef list<int>::iterator ListIterator;  // aliasing the set iterator type used

/* Function prototypes */

string promptUserForFile(ifstream & infile, string prompt);
bool testFileName(ifstream & infile, string filename);
void readFile(map<int, set<pair<int, int> > > & graph, ifstream & infile);
void print(map<int, set<pair<int, int> > > & graph);
void print(map<int, int> & distances);
void print(pair<map<int, int>, vector<pair<int, int> > > & heap);
void print(map<int, list<int> > & pathmap);
void print(map<int, int> & distances, map<int, list<int> > & pathmap);
int stringToInteger(string str);

void mainloop(map<int, set<pair<int, int> > > & graph, set<int> & processed, map<int, int> & distances, map<int, list<int> > & pathmap);
void initializeHeap(pair<map<int, int>, vector<pair<int, int> > > & heap, map<int, int> & distances);
void heapInsert(pair<map<int, int>, vector<pair<int, int> > > & heap, pair<int, int> node);
void heapBubbleUp(pair<map<int, int>, vector<pair<int, int> > > & heap, int nodeIndex);
void heapSwap(pair<map<int, int>, vector<pair<int, int> > > & heap, int nodeIndex1, int nodeIndex2);
void heapDelete(pair<map<int, int>, vector<pair<int, int> > > & heap, int node);
void heapBubbleDown(pair<map<int, int>, vector<pair<int, int> > > & heap, int nodeIndex);
void heapDeleteMin(pair<map<int, int>, vector<pair<int, int> > > & heap);

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
  // cout << "start: " << sourceNode << " max nodes: " << maxNodes << endl;

  /*
   * graph is a map with vertices as keys pointing to a
   * set of pair<int, int> which represent target nodes.
   * The first element of the pair is the node number and
   * the second of the pair is the edge length.
   */
  map<int, set<pair<int, int> > > graph;
  readFile(graph, infile);
  // print(graph);

  set<int> processed; // set with th vertices processed so far
  // processed.insert(sourceNode);  

  /*
   * distances is a map containing the computed shortest path distances.
   * The key is the node number and the value is the distance.
   */
  map<int, int> distances;
  for (MapIterator it = graph.begin(); it != graph.end(); ++it) {  // set all distances to max
    distances[it -> first] = MAX_DIST;
  }

  /*
   * pathmap is a map containing all shortest paths.
   * the key is the node and each element is a list
   * with the shortest path nodes for the key node.
   */
  map<int, list<int> > pathmap;

  distances[sourceNode] = 0; // set distance to source node equal to zero
  pathmap[sourceNode]; // set shortest path for source node to empty set

  // print(distances);

  // lets start
  mainloop(graph, processed, distances, pathmap);

  // print(pathmap);
  print(distances, pathmap);

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
void mainloop(map<int, set<pair<int, int> > > & graph, set<int> & processed, map<int, int> & distances, map<int, list<int> > & pathmap) {
  int graph_size = graph.size();
  int min_node, min_node_value;
  int edge_node, edge_length, edge_value, edge_index;
  int greedy_score;
  set<pair <int, int> > target_nodes;

  vector<pair<int, int> > nodes_heap; // heap containing the remaining nodes with their min distances
  map<int, int> heap_map; // map from node number to heap vector index for accessing elements in heap
  pair<map<int, int>, vector<pair<int, int> > > heap; // representing heap including map and vector
  heap = make_pair(heap_map, nodes_heap);
  initializeHeap(heap, distances);

  for (int i = 0; i < graph_size; i++) {
    // Extract min and update distances
    min_node = heap.second[0].first;  // extract min
    min_node_value = heap.second[0].second; // mind the value
    processed.insert(min_node);
    distances[min_node] = min_node_value;
    heapDeleteMin(heap); // min was extracted, now we can delete it

    // Maintain invariants in heap
    target_nodes = graph[min_node];
    for (SetIterator edge_it = target_nodes.begin(); edge_it != target_nodes.end(); ++edge_it) {
      edge_node = edge_it -> first; // a target node from the min node
      if (processed.count(edge_node) == 0) { // target node is still on the heap
	edge_length = edge_it -> second; // the length between min node and target node
	edge_index = heap.first[edge_node];
	edge_value = heap.second[edge_index].second; // the current calculated path length of the target node
	greedy_score = min_node_value + edge_length; // new greedy score for the target node
	// cout << "min: " << min_node << " edge: " << edge_node << " val: " << edge_value << " score: " << greedy_score << endl;
	if (greedy_score < edge_value) { // if new score is better than old score
	  heapDelete(heap, edge_index);
	  heapInsert(heap, make_pair(edge_node, greedy_score));
	}
      }
    }
  }
}

void initializeHeap(pair<map<int, int>, vector<pair<int, int> > > & heap, map<int, int> & distances) {
  vector<pair<int, int> > nodes_heap = heap.second;
  for (MapIntIterator it = distances.begin(); it != distances.end(); ++it) {
    heapInsert(heap, make_pair(it -> first, it -> second)); // heap consists of pairs (node number, min path distance)
  }
}

void heapInsert(pair<map<int, int>, vector<pair<int, int> > > & heap, pair<int, int> node) {
  int new_node_index = heap.second.size();
  heap.second.push_back(node);
  heap.first[node.first] = new_node_index; // add key for node with heap index into map
  heapBubbleUp(heap, new_node_index);
}

void heapBubbleUp(pair<map<int, int>, vector<pair<int, int> > > & heap, int nodeIndex) {
  int parent_node_index;
  if (nodeIndex == 0) parent_node_index = 0;
  else parent_node_index = (nodeIndex - 1) / 2; // i/2 if i even, floor(i/2) if i odd
  int parent_node_value = heap.second[parent_node_index].second;
  int node_value = heap.second[nodeIndex].second;
  if (node_value < parent_node_value) {
    heapSwap(heap, parent_node_index, nodeIndex);
    heapBubbleUp(heap, parent_node_index);
  }
}

void heapSwap(pair<map<int, int>, vector<pair<int, int> > > & heap, int nodeIndex1, int nodeIndex2) {
  pair<int, int> tmp = heap.second[nodeIndex1];
  heap.second[nodeIndex1] = heap.second[nodeIndex2]; // swap pairs in heap vector
  heap.second[nodeIndex2] = tmp;
  heap.first[heap.second[nodeIndex1].first] = nodeIndex1; // update keys in heap map
  heap.first[heap.second[nodeIndex2].first] = nodeIndex2;
}

void heapDelete(pair<map<int, int>, vector<pair<int, int> > > & heap, int nodeIndex) {
  heap.second[nodeIndex].second = -1;
  heapBubbleUp(heap, nodeIndex);
  heapDeleteMin(heap);
}

void heapDeleteMin(pair<map<int, int>, vector<pair<int, int> > > & heap) {
  int node = heap.second[0].first;
  int last_node_index = heap.second.size() - 1;
  heapSwap(heap, 0, last_node_index);
  heap.second.pop_back();
  heap.first.erase(node);
  heapBubbleDown(heap, 0);
}


void heapBubbleDown(pair<map<int, int>, vector<pair<int, int> > > & heap, int nodeIndex) {
  int node_value = heap.second[nodeIndex].second;
  int vec_size = heap.second.size();
  int child_node1_index = nodeIndex * 2 + 1; // left child at 2i (if exists)
  int child_node2_index = nodeIndex * 2 + 2; // right child at 2i+1 (if exists)
  int child_node1_value = MAX_DIST;
  int child_node2_value = MAX_DIST;

  if (child_node1_index < vec_size) { // otherwise there is no left child
    child_node1_value = heap.second[child_node1_index].second;
  }
  if (child_node2_index < vec_size) { // otherwise there is no right child
    child_node2_value = heap.second[child_node2_index].second;
  }

  if (child_node1_value <= child_node2_value) {
    if (node_value > child_node1_value) {
      heapSwap(heap, child_node1_index, nodeIndex);
      heapBubbleDown(heap, child_node1_index);
    }
  } else if (node_value > child_node2_value) {
    heapSwap(heap, child_node2_index, nodeIndex);
    heapBubbleDown(heap, child_node2_index);
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

void print(map<int, int> & distances) {
  for (MapIntIterator it = distances.begin(); it != distances.end(); ++it) {
    cout << it -> first << " => " << it -> second << ", ";
  }
  cout << endl;
}

void print(pair<map<int, int>, vector<pair<int, int> > > & heap) {
  vector<pair<int, int> > nodes_heap = heap.second;
  int vec_max = nodes_heap.size();
  for (int i = 0; i < vec_max; i++) {
    pair<int, int> node = nodes_heap[i];
    cout << node.first << "->" << node.second << ", ";
  }
  cout << endl;
  // print(heap.first);
}


void print(map<int, list<int> > & pathmap) {
  list<int> mlist;
  for (MapListIterator it = pathmap.begin(); it != pathmap.end(); ++it) {
    mlist = it -> second;
    cout << it -> first << " => [";
    for (ListIterator it2 = mlist.begin(); it2 != mlist.end(); ++it2) {
      cout << *it2 << ", ";
    }
    cout << "]" << endl;
  }
}

void print(map<int, int> & distances, map<int, list<int> > & pathmap) {
  list<int> mlist;
  int mnode, path_length; 
  for (MapIntIterator it = distances.begin(); it != distances.end(); ++it) {
    mnode = it -> first;
    path_length = it -> second;
    mlist = pathmap[mnode];
    cout << mnode << " => " << path_length << " [";
    for (ListIterator it2 = mlist.begin(); it2 != mlist.end(); ++it2) {
      cout << *it2 << ", ";
    }
    cout << "]" << endl;
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
