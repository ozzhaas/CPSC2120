#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;



int main () {
    int aliceSum = 0;
    int barbSum = 0;
    string inputLine;

    cin >> inputLine;

    int i = 0;
    while (i < inputLine.length()) {
        if (inputLine[i] == 'A') {
            aliceSum = aliceSum + (stoi(inputLine[i + 1]));
        }
        else if (inputLine[i] == 'B') {
            barbSum = barbSum + (stoi(inputLine[i + 1]));
        }
    }


    if (aliceSum > barbSum) {
        cout << "A" << endl;
    }
    else {
        cout << "B" << endl;
    }


    return 0;
}
