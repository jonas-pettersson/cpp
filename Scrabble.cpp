/*
 * File: Scrabble.cpp
 * -------------------
 * Play a game of scrabble!
 * Each uppercase letter is scored according to
 * their scrabble value, and the sum is printed.
 */

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
  string word;
  int sum = 0;
  cout << "Please enter your Scrabble word: ";
  cin >> word;
  for (int i = 0; i < word.length(); i++) {
    switch (word[i]) {
    case 'A': case 'E': case 'I': case 'L': case 'N': case 'O': case 'R': case 'S': case 'T': case 'U':
      sum++;
    case 'D': case 'G':
      sum += 2;
    case 'B': case 'C': case 'M': case 'P':
      sum += 3;
    case 'F': case 'H': case 'V': case 'W': case 'Y':
      sum += 4;
    case 'K':
      sum += 5;
    case 'J': case 'X':
      sum += 8;
    case 'Q': case 'Z':
      sum += 10;
    }
  }
  cout << "Score: " << sum << endl;
  return 0;
}
