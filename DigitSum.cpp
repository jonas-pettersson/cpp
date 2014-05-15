/*
 * File: DigitSum.cpp
 * ------------------
 * Calculates the sums of the digits in an integer.
 * And also illustrates limitation in the cin function.
*/

#include <iostream>
using namespace std;

long digitSum(long n);

int main() {
  long aNumber;
  cout << "Enter an integer: ";
  cin >> aNumber;
  cout << "Actually registered number: " << aNumber << endl;
  cout << "Sum: " << digitSum(aNumber) << endl;
  return 0;
}

long digitSum(long n) {
  long sum = 0;
  while (n > 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}
