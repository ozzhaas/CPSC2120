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
#include <vector>

using namespace std;



struct Candy {
    int weight;
    int value;
};

const int N = 16;
Candy candies[N];
int maxWeight = 2000;

struct Bag {
    int weight;
    int totalVal;
    vector<Candy> candies_in_bag;
};



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


void greedy() {
    bool stored_candies[N];
    Bag bag1, bag2, bag3;
    sort_tasty();


    for (int i = N - 1; i >= 0; i--) {
        if (bag1.weight + candies[i].weight < 2000 && stored_candies[i] != true) {
            bag1.weight += candies[i].weight;
            bag1.candies_in_bag.push_back(candies[i]);
            stored_candies[i] = true;
            bag1.totalVal += candies[i].value;
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        if (bag2.weight + candies[i].weight < 2000 && stored_candies[i] != true) {
            bag2.weight += candies[i].weight;
            bag2.candies_in_bag.push_back(candies[i]);
            stored_candies[i] = true;
            bag2.totalVal += candies[i].value;
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        if (bag3.weight + candies[i].weight < 2000 && stored_candies[i] != true) {
            bag3.weight += candies[i].weight;
            bag3.candies_in_bag.push_back(candies[i]);
            stored_candies[i] = true;
            bag3.totalVal += candies[i].value;
        }
    }

    cout << "Candy in Bag1: " << endl;
    for (unsigned int i = 0; i < bag1.candies_in_bag.size(); i++) {
        cout << bag1.candies_in_bag[i].weight << " " << bag1.candies_in_bag[i].value << endl;
    }
    cout << endl;

    cout << "Candy in Bag2: " << endl;
    for (unsigned int i = 0; i < bag2.candies_in_bag.size(); i++) {
        cout << bag2.candies_in_bag[i].weight << " " << bag2.candies_in_bag[i].value << endl;
    }
    cout << endl;

    cout << "Candy in Bag3: " << endl;
    for (unsigned int i = 0; i < bag3.candies_in_bag.size(); i++) {
        cout << bag3.candies_in_bag[i].weight << " " << bag3.candies_in_bag[i].value << endl;
    }
    cout << endl;

    cout << "Greedy: " << bag1.totalVal + bag2.totalVal + bag3.totalVal << endl;
}



int main (void) {
    ifstream input;
    input.open("candy.txt");
    string line;
    string valString;
    string weightString;
    int tempVar = 0;
    int i = 0;



    while (input >> tempVar) {
        Candy tempCandy;
        tempCandy.weight = tempVar;
        input >> tempVar;
        tempCandy.value = tempVar;
        candies[i] = tempCandy;
        i++;
    }


    greedy();

    return 0;
}
