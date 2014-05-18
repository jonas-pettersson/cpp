/*
 * File: GCD.cpp
 * -------------
 * This program calculates the greatest common divisor
 * for two numbers, x and y, entered by the user.
 * The calculation is based on Euclid's algorithm.
 */

#include <iostream>
using namespace std;

int gcd(int x, int y);

int main() {
  int x, y;
  cout << "Greatest Common Divisor." << endl;
  cout << "Enter x: ";
  cin >> x;
  cout << "Enter y: ";
  cin >> y;
  cout << "GCD: " << gcd(x, y) << endl;
  return 0;
}

int gcd (int x, int y) {
  int r = x % y;
  while (r != 0) {
    x = y;
    y = r;
    r = x % y;
  }
  return y;
}

