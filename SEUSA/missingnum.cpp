#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;




int main (void) {

    //number of nums written on board//
    int n = 0;
    char input1;
    char input2;
    string newNum;

    //numbers on the board in order (excluding the one that was erased)//
    cin >> n;

    int inputArr[n];

    for (int i = 0; i < 9; i++) {
        cin >> input1;
        int intInput1 = input1 - '0';
        inputArr[i] = intInput1;
    }


    for (int i = 9; i < n-1; i++) {
        cin >> input1;
        cin >> input2;
        newNum += input1;
        newNum += input2;
        inputArr[i] = stoi(newNum);
        input1 = '0';
        input2 = '0';
        newNum = "";
    }



    for (int i = 1; i < n - 1; i++) {
        if ((inputArr[i + 1] - inputArr[i]) > 1) {
            cout << inputArr[i] + 1 << endl;
            return 0;
        }
    }

//      13          11
// input[i+1] - input[i] = 2
// input[i] + 1 = 12


    return 0;
}
