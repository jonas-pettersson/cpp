/*
 * File: PrintASCII.cpp
 * --------------------
 * This program prints all printable ASCII codes
 */

#include <iostream>
#include <cctype>
#include <sstream>
using namespace std;

string integerToString(int n);

main() {
  char c;
  for (int i = 0; i < 256; i++) {
    c = i;
    cout << integerToString(i) << " ";
    if (isprint(c)) {
      cout << c << " ";
    }
    if (i%10 == 0) cout << endl;
  }
  return 0;
}

string integerToString(int n) {
    ostringstream stream;
    stream << n;
    return stream.str();
}
