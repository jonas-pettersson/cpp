/*
 * File: PrimesTest.cpp
 * --------------------
 * This program tests the implementation of the primes library.
 */

#include <iostream>
#include "primes.h"
using namespace std;

int main() {
  int n;
  cout << "Please enter integer: ";
  cin >> n;
  if ( isPrime(n) )
    cout << n << " is a prime." << endl;
 else
   cout << n << " is not a prime" << endl;
  return 0;
}
