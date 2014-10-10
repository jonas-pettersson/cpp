/*
 * File: FindDNAMatch.cpp
 * ----------------------
 * Find positions at which a DNA strand
 * can attach to another strand.
 */

#include <iostream>
#include <string>
#include <cctype>
#include "lib/strlib.h"
using namespace std;

/* Function prototypes */
int findDNAMatch(string s1, string s2, int start = 0);
bool dnaCombines(char base1, char base2);

int main() {
  string strand1;
  string strand2;
  cout << "Enter DNA strand 1: ";
  cin >> strand1;
  cout << "Enter DNA strand 2: ";
  cin >> strand2;
  int match = 99;
  string matches;
  int start = 0;
  while (match > 0 && start < strand1.length()) {
    match = findDNAMatch(strand1, strand2, start);
    if (!(match < 0)) {
      matches += integerToString(match);
      matches += ' ';
      start = match + 1;
    } else start++;
  }  
  if (matches.length() < 1 ) {
    cout << "No match!" << endl;
  } else {
    cout << "DNA matches at position: " << matches << endl;
  }
  return 0;
}

/*
 * Function: findDNAMAtch
 * Usage: int match = findDNAMAtch(strand1, strand2, start)
 * --------------------------------------------------------
 * Returns the first position at which the DNA strand s1 can attach to the
 * strand s2. The optional start parameter indicates the index position at
 * which the search should start. If there is no match return -1
 */
int findDNAMatch(string s1, string s2, int start) {
  for (int i = start; i < (s1.length() - s2.length()); i++) {
    for (int j = 0; j < s2.length(); j++) {
      if (!dnaCombines(s1[j + i], s2[j])) {
	break;
      }
      if (j == s2.length() -1) return i;
    }
  }
  return -1;
}

/*
 * Function: dnaCombines
 * Usage: bool combines = dnaCombines(base1, base2)
 * ------------------------------------------------
 * Returns true if a base combines with another base.
 * A base needs to be a character A, C, G, or T.
 * DNA bases combine with each other only in the following ways:
 * Cytosine (C) links only with guanine (G), and vice versa.
 * Adenosine (A) links only with thymine (T), and vice versa.
 */
bool dnaCombines(char base1, char base2) {
  if (base1 == 'A') return (base2 == 'T');
  if (base1 == 'T') return (base2 == 'A');
  if (base1 == 'C') return (base2 == 'G');
  if (base1 == 'G') return (base2 == 'C');
  return false;
}
