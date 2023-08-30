// Created by Tedla Boke on 8/28/23.
// NetID: uq6435
// Email: tboke@horizon.csueastbay.edu

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

// A function to check if a string is a valid number
bool is_valid_number(const string& s) {
    for (char c : s) {
        if (!isdigit(c) && c != '.' && c != '-') return false;
    }
    return true;
}

int main() {
    const int MaxRows = 1000;
    int firstColumn[MaxRows];
    int secondColumn[MaxRows];
    int rowCount = 0;
    string invalidNumbers;

    while (true) {
        char filename[100];
        cout << "Please input the filename: ";
        cin >> filename;

        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cerr << "Error opening file " << filename << ". Please try again." << endl;
            continue;
        }

        rowCount = 0;
        invalidNumbers = "";
        while (rowCount < MaxRows) {
            string line;
            if (!getline(inputFile, line)) {
                break;
            }

            istringstream iss(line);
            string num1, num2;
            if (getline(iss, num1, ',') && getline(iss, num2)) {
                if (is_valid_number(num1) && is_valid_number(num2)) {
                    firstColumn[rowCount] = stoi(num1);
                    secondColumn[rowCount] = stoi(num2);
                    rowCount++;
                } else {
                    if (!invalidNumbers.empty()) {
                        invalidNumbers += ", ";
                    }
                    invalidNumbers += num1 + ", " + num2;
                }
            }
        }

        if (rowCount == 0) {
            cerr << "No valid data found in the file." << endl;
            inputFile.close();
            continue;
        }

        inputFile.close();
        break;
    }

    int sumFirstColumn = 0;
    int largestSecondColumn = numeric_limits<int>::min();

    for (int i = 0; i < rowCount; ++i) {
        sumFirstColumn += firstColumn[i];
        if (secondColumn[i] > largestSecondColumn) {
            largestSecondColumn = secondColumn[i];
        }
    }

    double averageFirstColumn = static_cast<double>(sumFirstColumn) / rowCount;

    cout.precision(4);
    cout << "The average value of all numbers in the first column: " << fixed << averageFirstColumn << endl;
    cout << "The largest value of all numbers in the second column: " << largestSecondColumn << endl;
    cout << "The total number of rows in the file is: " << rowCount << endl;

    if (!invalidNumbers.empty()) {
        cout << "The invalid numbers are: " << invalidNumbers << endl;
    }

    return 0;
}
