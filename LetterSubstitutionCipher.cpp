/*
 * File: LetterSubstitutionCipher.cpp
 * ----------------------
 * This program implements the letter substitution cipher
 * in which you replace each letter in the original
 * message by by an arbitrary letter from a
 * translation table.
 */

#include <iostream>
#include <string>
#include <cctype>
#include "lib/simpio.h"
using namespace std;

/* Function prototypes */
string encodeLetterSubstitutionCipher(string str, string translation);

/* Main program */
int main() {
  cout << "Letter Substitution Cipher." << endl;
  string translation = getLine("Enter a 26-letter key: ");
  string message = getLine("Enter a message: ");
  cout << "Encoded message: " << encodeLetterSubstitutionCipher(message, translation) << endl;
  return 0;
}


string encodeLetterSubstitutionCipher(string str, string translation) {
  char newChar;
  for (int i = 0; i < str.length(); i++) {
    if (isupper(str[i])) {
      str[i] = translation[str[i] - 'A'];
    }
  }
  return str;
}
