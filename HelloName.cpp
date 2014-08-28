/*
 * File: HelloName.cpp
 * -------------------
 * This program extends the classic "Hello world" program by asking
 * the user for a name, which is then used as part of the greeting.
 * This version of the program reads a complete line into name and
 * not just the first word.
 */

#include <iostream>
#include <string>
#include "lib/simpio.h"
using namespace std;

int main() {
  string name = getLine("Skriv ditt namn: ");
  cout << "*** Hej " << name << "!!! ***" << endl;
  return 0;
}
