/*
 * File: QuickSort.cpp
 * -----------------------
 * This program is an implementation of the quick sort
 * algorithm to sort a list of integers. It reads integers from a file
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
unsigned long quickSort(vector<long> & vec, int start, int end);
int choosePivot(vector<long> & vec, int l, int r);
int partition(vector<long> & vec, int l, int r);
void swap(vector<long> & vec, int i, int j);
bool testFileName(ifstream & infile, string filename);
void readFile(vector<long> & vec, ifstream & infile);
void print(vector<long> & vec);
void print_h(vector<long> & vec);

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
  unsigned long count;
  count = quickSort(in_numbers, 0, in_numbers.size() - 1);
  print(in_numbers);
  cout << "Comparisons: " << count << endl;
  return 0;
}

/*
 * Function: quickSort
 * -------------------
 * This function sorts the integers in vector between indexes
 * strt and end inclusive using the quick sort algorithm with following steps:
 *
 * (1) If vector-size = 1 return.
 * (2) Partition vector around p.
 * (3) Recurse on the first part of vector (the subarray of elements less than the pivot).
 * (4) Recurse on the second part of vector (the subarray of elements greater than the pivot).
 */
unsigned long quickSort(vector<long> & vec, int start, int end) {
  unsigned long count = 0;
  if (start >= end) return count; // vecor size is 1 or less
  int pivot = partition(vec, start, end);
  count += end - start; // add m - 1 for each sub-vector of size m
  count += quickSort(vec, start, pivot - 1);
  count += quickSort(vec, pivot + 1, end);
  return count;
  }

/*
 * Function: choosePivot
 * ---------------------
 * This function chooses the pivot element for quick sort.
 * It returns the index of the pivot element.
 */
int choosePivot(vector<long> & vec, int l, int r) {
  // return l; // pivot is the first element of the array

  // swap(vec, l, r); // pivot is the last element of the array
  // return l;

  int m = l + (r - l) / 2; // pivot is median of three selected elements
  int median;
  if ((vec[l] <= vec[m] && vec[m] <= vec[r]) || 
      (vec[r] <= vec[m] && vec[m] <= vec[l])) median = m;
  else if ((vec[m] <= vec[r] && vec[r] <= vec[l]) ||
	   (vec[l] <= vec[r] && vec[r] <= vec[m])) median = r;
  else median = l;
  swap(vec, l, median);
  return l;
}

/*
 * Function: partition
 * -------------------
 * This function partitions the vector according to the
 * quick sort algorithm and returns the resulting partitioning
 * index. In the resulting array, the element at index i is
 * the pivot element, elements at indexes less than i are less
 * than the pivor element and elements at indexes larger than i
 * are larger than the pivot element.
 */
int partition(vector<long> & vec, int l, int r) {
  // print_h(vec);
  // cout << "part: " << l << ", " << r << endl;  
  int p = choosePivot(vec, l, r);
  // cout << "p: " << p << endl;
  int p_value = vec[p];
  int i = l + 1;
  for (int j = l + 1; j < r + 1; j++) {
    if (vec[j] < p_value) { // if vec[j] > p do nothing
      swap(vec, i, j);
      i++;
    }
  }
  // if (r - l <= 1 && vec[i] <= p_value) swap(vec, l, i);
  swap(vec, l, i - 1);
  return i - 1;
}

/* 
 * Function: swap
 * --------------
 * This function swaps the elements with indexes i and j
 * in the vecor.
 */
void swap(vector<long> & vec, int i, int j) {
  // print_h(vec);
  // cout << "swap: " << i << ", " << j << endl;
  int tmp = vec[i];
  vec[i] = vec[j];
  vec[j] = tmp;
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
 * Usage: vector<int> vec; print(vec);
 * ------------------------------------
 * Prints the content of a vector, one item per line.
 */
void print(vector<long> & vec) {
  long n = vec.size();
  for (long i = 0; i < n; i++) {
    cout << vec[i] << endl;
  }
  // cout << endl;
}

/*
 * Function: print_h
 * -----------------
 * Prints the elements of a vector horisontally,
 * separated by a comma
 */
void print_h(vector<long> & vec) {
  long n = vec.size();
  for (long i = 0; i < n; i++) {
    cout << vec[i] << ", ";
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
