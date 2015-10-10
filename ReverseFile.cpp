/*
 * File: ReverseFile.cpp
 * ---------------------
 * This program displays the lines of an input file in reverse order.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "lib/filelib.h"
#include "lib/vector.h"
using namespace std;

/* Function prototypes */

void readEntireFile(istream & is, Vector<string> & lines);
string promptUserForFile(ifstream & infile, string prompt);

/* Main program */

int main() {
  ifstream infile;
  Vector<string> lines;
  promptUserForFile(infile, "Input file: ");
  readEntireFile(infile, lines);
  infile.close();
  for (int i = lines.size() - 1; i >= 0; i--) {
    cout << lines[i] << endl;
  }
  return 0;
}

/*
 * Function: readEntireFile
 * Usage: readEntireFile(is, lines);
 * ---------------------------------
 * Reads the entire contents of the specified input stream into the
 * string vector lines. The client is responsible for opening and
 * closing the stream.
 */
void readEntireFile(istream & is, Vector<string> & lines) {
  while (true) {
    string line;
    getline(is, line);
    if (is.fail()) break;
    lines.add(line);
  }
}

string promptUserForFile(ifstream & infile, string prompt) {
  while (true) {
    cout << prompt;
    string filename;
    getline(cin, filename);
    infile.open(filename.c_str());
    if (!infile.fail()) return filename;
    infile.clear();
    cout << "Unable to open that file. Try again." << endl;
    if (prompt == "") prompt = "Input file: ";
  }
}
