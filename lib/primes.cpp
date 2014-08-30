/*
 * File: primes.cpp
 * ----------------
 * This file implements the primes interface.
 */

#include <iostream>
using namespace std;

/*
 * Implementation notes: primes
 * ----------------------------
 * This function uses a primitive algorithm to determine
 * if a number is pime or not.
 */

bool isPrime(int n) {
  if ( n <= 0 ) return false;
  if ( n == 1 ) return true;
  if ( n % 2 == 0 ) return false;
  if ( n % 3 == 0 ) return false;
  for ( int i = 5; i < n; i += 2) {
     if ( n % i == 0 ) return false;
  }
  return true;
}
