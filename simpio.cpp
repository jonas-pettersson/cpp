/*
 * File: simpio.cpp
 * ----------------
 * This file implements the simpio.h interface.
 */

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "simpio.h"
using namespace std;

static void appendSpace(string& prompt);

/*
 * Implementation notes: getInteger, getReal
 * -----------------------------------------
 * Each of these functions reads a complete input line and then uses the
 * <sstream> library to parse that line into a value of the desired type.
 * If that fails, the implementation asks the user for a new value.
 */

int getInteger(string prompt, string reprompt) {
    if (reprompt == "") {
        reprompt = "Illegal integer format. Try again.";
    }
    appendSpace(prompt);
    int value;
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        istringstream stream(line);
        stream >> value >> ws;
        if (!stream.fail() && stream.eof()) break;
        cout << reprompt << endl;
        if (prompt == "") prompt = "Enter an integer: ";
    }
    return value;
}

double getReal(string prompt, string reprompt) {
    if (reprompt == "") {
        reprompt = "Illegal numeric format. Try again.";
    }
    appendSpace(prompt);
    double value;
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        istringstream stream(line);
        stream >> value >> ws;
        if (!stream.fail() && stream.eof()) break;
        cout << reprompt << endl;
        if (prompt == "") prompt = "Enter a number: ";
    }
    return value;
}

bool getYesOrNo(string prompt, string reprompt) {
    if (reprompt == "") {
        reprompt = "Please type a word that starts with 'Y' or 'N'.";
    }
    appendSpace(prompt);
    bool value;
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        if ((int) line.length() > 0) {
            char first = tolower(line[0]);
            if (first == 'y') {
                value = true;
                break;
            } else if (first == 'n') {
                value = false;
                break;
            }
        }
        cout << reprompt << endl;
        if (prompt == "") prompt = "Try again: ";
    }
    return value;
}

/*
 * Implementation notes: getLine
 * -----------------------------
 * The getLine function simply combines the process of displaying a
 * prompt and reading an input line into a single call.  The primary
 * reason for including this function in the library is to ensure
 * that the process of reading integers, floating-point numbers, and
 * strings remains as consistent as possible.
 */

string getLine(string prompt) {
    appendSpace(prompt);
    string line;
    cout << prompt;
    getline(cin, line);
    return line;
}

void getLine(string prompt, string& out) {
    appendSpace(prompt);
    string line;
    cout << prompt;
    getline(cin, out);
}

void getLine(istream& input, string& out) {
    getline(input, out);
}

static void appendSpace(string& prompt) {
    if (!prompt.empty() && !isspace(prompt[prompt.length() - 1])) {
        prompt += ' ';
    }
}
