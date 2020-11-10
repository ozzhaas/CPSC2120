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

struct Bag {
    int weight;
    int totalVal;
    Candy candies_in_bag;
};


const int N = 16;
Candy candies[N];
int maxWeight = 2000;

int max (int a, int b) {
    return (a > b) ? a : b;
}

void sort_tasty() {
    int i, j, min;
    for (i = 0; i < N - 1; i++) {
        min = i;
        for (j = i + 1; j < N; j++) {
            if (candies[j].value < candies[min].value) {
                min = j;
            }
        }
        swap(candies[min], candies[i]);
    }
}



int main (void) {
    ifstream input;
    input.open("candy.txt");
    string line;
    string valString;
    string weightString;
    int tempVar = 0;
    int i = 0;
    bool stored_candies[N];
    Bag bag1, bag2, bag3;


    while (input >> tempVar) {
        Candy tempCandy;
        tempCandy.weight = tempVar;
        input >> tempVar;
        tempCandy.value = tempVar;
        candies[i] = tempCandy;
        i++;
    }

    sort_tasty();

    for (int i = N - 1; i >= 0; i--) {
        if (bag1.weight + candies[i].weight < 2000 && stored_candies[i] != true) {
            bag1.weight += candies[i].weight;
            stored_candies[i] = true;
            bag1.totalVal += candies[i].value;
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        if (bag2.weight + candies[i].weight < 2000 && stored_candies[i] != true) {
            bag2.weight += candies[i].weight;
            stored_candies[i] = true;
            bag2.totalVal += candies[i].value;
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        if (bag3.weight + candies[i].weight < 2000 && stored_candies[i] != true) {
            bag3.weight += candies[i].weight;
            stored_candies[i] = true;
            bag3.totalVal += candies[i].value;
        }
    }

    cout << "Greedy: " << bag1.totalVal + bag2.totalVal + bag3.totalVal << endl;


    return 0;
}
