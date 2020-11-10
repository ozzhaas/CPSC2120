/*Kellen Haas
  CPSC 2120
  HW 03
  11/10/2020
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <cstdlib>

using namespace std;


struct Candy {
    int weight;
    int value;
};

const int N = 16;
Candy candies[N];
int maxWeight = 2000;

int max (int a, int b) {
    return (a > b) ? a : b;
}


int main (void) {
    ifstream input;
    input.open("candy.txt");
    string line;
    string valString;
    string weightString;
    Candy inputArray[N];

    for (int i = 0; i < N; i++) {
        input >> line;
        stringstream candySS(line);
        getline(candySS, weightString, ' ');
        getline(candySS, valString, ' ');
        Candy tempCandy;
        int tempW = stoi(weightString);
        int tempV = stoi(valString);
        tempCandy.weight = tempW;
        tempCandy.value = tempV;
        inputArray[i] = tempCandy;
    }


    for (int i = 0; i < N; i++) {
        cout << "Weight: " << inputArray[i].weight << "         " << "Value: "
             << inputArray[i].value << endl;
    }

    return 0;
}
