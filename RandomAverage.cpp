/*
 * File: RandomAverage.cpp
 * -----------------------
 * This program repeatedly generates a random
 * real number between  0 and 1 and then displays
 * the average after a specified number of trials
 * entered by the user.
 */

#include <iostream>
# include "random.h"
using namespace std;

int main() {
  int n;  
  cout << "Number of trials: ";
  cin >> n;
  double sum;
  for (int i = 0; i < n; i++) {
    sum += randomReal(0, 1);
  }
  cout << "Average: " << sum / n << endl;
  return 0;
}
