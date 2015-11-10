/*
 * File: MergeSort.cpp
 * -----------------------
 * This program is an implementation of the merge sort
 * algorithm. It reads characters from std input
 * and writes the sorted result to std output.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/* Function prototypes */

string promptUserForFile(ifstream & infile, string prompt);
void sort(vector<int> & vec);
void merge(vector<int> & vec, vector<int> & vec1, vector<int> & vec2);
bool testFileName(ifstream & infile, string filename);
void readFile(vector<int> & vec, ifstream & infile);
void print(vector<int> & vec);

/* Main program */

using namespace std;

int main(int argc, char* argv[]) {
  vector<int> in_numbers;
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
  readFile(in_numbers, infile);
  sort(in_numbers);
  print(in_numbers);
  return 0;
}

/*
 * Function: sort
 * --------------
 * This function sorts the elements of the vector into increasing order
 * using the merge sort algorithm, which consists of the following steps:
 *
 * 1. Divide the vector into two halves.
 * 2. Sort each of these smaller vectors recursively.
 * 3. Merge the two vectors back into the original one.
 */
void sort(vector<int> & vec) {
  int n = vec.size();
  if (n <= 1) return;
  vector<int> vec1;
  vector<int> vec2;
  for (int i = 0; i < n; i++) {
    if (i < n / 2) 
      vec1.push_back(vec[i]);
    else 
      vec2.push_back(vec[i]);  
  }
  sort(vec1);
  sort(vec2);
  vec.clear();
  merge(vec, vec1, vec2);
}

/*
 * Function: merge
 * ---------------
 * This function merges two sorted vectors, v1 and v2, into the vector
 * vec, which should be empty before this operation. Because the input
 * vectors are sorted, the implementation can always select the first
 * unused element in one of the input vectors to fill the next position.
 */
void merge(vector<int> & vec, vector<int> & vec1, vector<int> & vec2) {
  int n1 = 0;
  int n2 = 0;
  int vec1size = vec1.size();
  int vec2size = vec2.size();
  while (n1 < vec1size && n2 < vec2size) {
    if (vec1[n1] < vec2[n2]) {
      vec.push_back(vec1[n1++]);
    } else {
      vec.push_back(vec2[n2++]);
    }
  }
  while (n1 < vec1size) vec.push_back(vec1[n1++]);
  while (n2 < vec2size) vec.push_back(vec2[n2++]);
}

/*
 * Function: readFile
 * Usage: vector<int> vec; readFile(vec);
 * --------------------------------------
 * Asks for a file with numbers and reads the numbers into the vector;
 */
void readFile(vector<int> & vec, ifstream & infile) {
  int value;
  while (infile >> value) {
    vec.push_back(value);
  }
  infile.close();
}

/*
 * Function: print
 * Usage: vector<int> vec = print(vec);
 * ------------------------------------
 * Prints the content of a vector, one item per line.
 */
void print(vector<int> & vec) {
  int n = vec.size();
  for (int i = 0; i < n; i++) {
    cout << vec[i] << endl;
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
