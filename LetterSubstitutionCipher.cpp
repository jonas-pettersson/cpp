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
string encodeLetterSubstitutionCipher(string str, string encryptionKey);
string invertKey(string encryptionKey);

/* Main program */
int main() {
  cout << "Letter Substitution Cipher." << endl;
  string encryptionKey = getLine("Enter a 26-letter key: ");
  string message = getLine("Enter a message: ");
  string encodedMessage = encodeLetterSubstitutionCipher(message, encryptionKey);
  cout << "Encoded message: " << encodedMessage << endl;
  string decryptionKey = invertKey(encryptionKey);
  cout << "Decryption key: " << decryptionKey << endl;
  cout << "Decrypted message: " << encodeLetterSubstitutionCipher(encodedMessage, decryptionKey) << endl;
  return 0;
}


string encodeLetterSubstitutionCipher(string str, string encryptionKey) {
  for (int i = 0; i < str.length(); i++) {
    if (isupper(str[i])) {
      str[i] = encryptionKey[str[i] - 'A'];
    }
  }
  return str;
}

string invertKey(string encryptionKey) {
  string decryptionKey = string(26, ' ');
  for (int i = 0; i < encryptionKey.length(); i++) {
    decryptionKey[encryptionKey[i] - 'A'] = 'A' + i;
  }
  return decryptionKey;
}
