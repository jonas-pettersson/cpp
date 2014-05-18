/*
 * File: DaysInMonth.cpp
 * ---------------------
 * This program gives the number of days in a month.
*/

#include <iostream>
using namespace std;

/* Constants */

enum Month {
  JANUARY = 1,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER
};

/* Function prototypes */

int daysInMonth(Month month, int year);
bool isLeapYear(int year);

/* Main program */

int main() {
  int year;
  int month;
  cout << "Enter a year: ";
  cin >> year;
  cout << "Enter a month: ";
  cin >> month;
  int numberOfDays = daysInMonth(Month(month), year);
  cout << "Days in month: " << numberOfDays << endl;
}

/*
 * Function: daysInMonth
 * Usage int d = daysInMonth(m, y);
 * -------------------------------
 * Returns the number of days in a month.
*/

int daysInMonth(Month month, int year) {
  switch(month) {
   case APRIL:
   case JUNE:
   case SEPTEMBER:
   case NOVEMBER:
     return 30;
   case FEBRUARY:
     return (isLeapYear(year)) ? 29 : 28;
   default:
     return 31;
  }
}

/*
 * Function: isLeapYear
 * Usage: bool b = isLeapYear(year);
 * ---------------------------------
 * Returns true if year is leap year, false otherwise.
*/

bool isLeapYear(int year) {
  return ((year % 4 == 0) && (year % 100 != 0))
    || (year % 400 == 0);
}
