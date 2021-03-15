/* Kellen Haas
   CPSC 4890
   ICPC Regionals Practice Competition
   Basketball One-on-One
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;



int main () {
    int aliceSum = 0;
    int barbSum = 0;
    string inputLine;

    getline(cin, inputLine);

    for (unsigned int i = 0; i < inputLine.length(); i++) {
        if (inputLine[i] == 'A') {
            int convert = inputLine[i + 1] - '0';
            aliceSum = aliceSum + convert;
        }
        else if (inputLine[i] == 'B') {
            barbSum = barbSum + (inputLine[i + 1] - '0');
        }
        if (aliceSum >= 10 && barbSum >= 10) {
            if ((inputLine[i] == 'A') && (aliceSum - barbSum >= 2)) {
                // if (abs(aliceSum - barbSum) <= 1) {
                //
                // }
                cout << "A" << endl;
                return 0;
            }
            else if ((inputLine[i] == 'B') && (barbSum - aliceSum >= 2)) {
                cout << "B" << endl;
                return 0;
            }
            // else if (aliceSum == barbSum) {
            //     cout << "tie?" << endl;
            //     return 0;
            // }
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
