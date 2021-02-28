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

    getline(cin, inputLine);

    for (unsigned int i = 0; i < sizeof(inputLine); i++) {
        if (inputLine[i] == 'A') {
            int convert = inputLine[i + 1] - '0';
            aliceSum = aliceSum + convert;
        }
        else if (inputLine[i] == 'B') {
            barbSum = barbSum + (inputLine[i + 1] - '0');
        }
    }

// A2B1A2B2A2A2A2

    if (aliceSum > barbSum) {
        cout << "A" << endl;
    }
    else {
        cout << "B" << endl;
    }


    return 0;
}
