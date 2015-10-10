/*
 * File: CountInversions.cpp
 * -----------------------
 * This program is an implementation of the count inversions
 * algorithm based on merge sort idea. It reads integers from a file
 * specified as the first argument of the program or prompted for
 * and writes the result to std output.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/* Function prototypes */

string promptUserForFile(ifstream & infile, string prompt);
unsigned long countInv(vector<long> & vec);
unsigned long mergeAndCount(vector<long> & vec, vector<long> & vec1, vector<long> & vec2);
bool testFileName(ifstream & infile, string filename);
void readFile(vector<long> & vec, ifstream & infile);
void print(vector<long> & vec);

/* Main program */

using namespace std;

int main(int argc, char* argv[]) {
  vector<long> in_numbers;
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
  cout << countInv(in_numbers) << endl;
  return 0;
}

/*
 * Function: countInv
 * --------------
 * This function counts the inversions of the integers in vector
 * using the merge sort algorithm as basis, consisting of the following steps:
 *
 * 1. Divide the vector into two halves.
 * 2. Sort and count inversions inside left and right vectors recursively.
 * 3. Count slit inversions when merging the two vectors back into the original one.
 */
unsigned long countInv(vector<long> & vec) {
  unsigned long l, r, s = 0; // left, right, and split counts
  long n = vec.size();
  if (n <= 1) return 0;
  vector<long> vec1;
  vector<long> vec2;
  for (long i = 0; i < n; i++) {
    if (i < n / 2) 
      vec1.push_back(vec[i]);
    else 
      vec2.push_back(vec[i]);  
  }
  l = countInv(vec1);
  r = countInv(vec2);
  vec.clear();
  s = mergeAndCount(vec, vec1, vec2);
  return l + r + s;
}

/*
 * Function: mergeAndCount
 * ---------------
 * This function merges two sorted vectors, v1 and v2, into the vector
 * vec, and simultaneously counts the umber of invertions split between these
 * two vectors.Because the input vectors are sorted, the implementation can always select the first
 * unused element in one of the input vectors to fill the next position.
 * In addition, it counts the number of invertions by recognizing the fact that
 * when an element of the 2nd array gets copied to vec it means that the remaining
 * elements in the 1st vector are inversions f this element. Thus increment
 * the count by the number of elements remaining in 1st array.
 */
unsigned long mergeAndCount(vector<long> & vec, vector<long> & vec1, vector<long> & vec2) {
  long n1 = 0;
  long n2 = 0;
  long vec1size = vec1.size();
  long vec2size = vec2.size();
  unsigned long count = 0;
  while (n1 < vec1size && n2 < vec2size) {
    if (vec1[n1] < vec2[n2]) {
      vec.push_back(vec1[n1++]);
    } else {
      vec.push_back(vec2[n2++]);
      count += vec1size - n1;
    }
  }
  while (n1 < vec1size) vec.push_back(vec1[n1++]);
  while (n2 < vec2size) vec.push_back(vec2[n2++]);
  return count;
}

/*
 * Function: readFile
 * Usage: vector<int> vec; readFile(vec);
 * --------------------------------------
 * Asks for a file with numbers and reads the numbers into the vector;
 */
void readFile(vector<long> & vec, ifstream & infile) {
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
void print(vector<long> & vec) {
  long n = vec.size();
  for (long i = 0; i < n; i++) {
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
