/*
 * File: CyclicCipher.cpp
 * ----------------------
 * This program implements the cyclic cipher
 * in which you replace each letter in the original
 * message by the letter that appears a fixed distance
 * ahead in the alphabet.
 */

#include <iostream>
#include <string>
#include <cctype>
#include "lib/simpio.h"
using namespace std;

/* Function prototypes */
string encodeCaesarCipher(string str, int shift);

/* Main program */
int main() {
  cout << "This program encodes a message using a Caesar cipher." << endl;
  int shift = getInteger("Enter the number of character positions to shift: ");
  string message = getLine("Enter a message: ");
  cout << "Encoded message: " << encodeCaesarCipher(message, shift) << endl;
  return 0;
}


string encodeCaesarCipher(string str, int shift) {
  char newChar;  
  for (int i = 0; i < str.length(); i++) {
    if (isalpha(str[i])) {
      newChar = str[i] + shift;
      if ((!isalpha(newChar)) || (isupper(newChar) != isupper(str[i]))) {
	if (shift > 0) {
	  str[i] = newChar - 26;
	} else {
	  str[i] = newChar + 26;
	}
      } else {
	str[i] = newChar;
      }
    }
  }
  return str;
}
