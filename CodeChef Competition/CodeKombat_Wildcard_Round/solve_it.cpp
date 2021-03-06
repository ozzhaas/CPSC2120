/*Kellen Haas
  CPSC 4890
  Coding Competition
  12/8/2020
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>


using namespace std;



int main() {
    int testcases;

    ifstream input;
    input.open("input.txt");

    input >> testcases;

    while(testcases--) {
        int N = 0;
        int K = 0;

        input >> N >> K;
        int array[N];
        for (int i = 0; i < N; i++) {
            input >> array[i];
        }
            sort(array, array + N);

            int maximum = array[0];
            int minimum = array[N - 1];

            cout << (minimum + K) - (maximum - K) << endl;
    }

    input.close();

    return 0;
}
