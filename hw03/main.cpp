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
    int weight = 0;
    int value = 0;
};

const int N = 16;
const int T = 1000;
Candy candies[N];
int maxWeight = 2000;
bool stored_candies[N];


struct Bag {
    int weight = 0;
    int totalVal = 0;
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


void shuffle() {
    for (int i = 0; i < N; i++) {
        int temp = rand() % (i + 1);
        swap(candies[i], candies[temp]);
    }
}


int greedy() {
    Bag bag1, bag2, bag3;
    bag1.candies_in_bag.clear();
    bag2.candies_in_bag.clear();
    bag3.candies_in_bag.clear();

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

    // cout << "Candy in Bag1: " << endl;
    // for (unsigned int i = 0; i < bag1.candies_in_bag.size(); i++) {
    //     cout << bag1.candies_in_bag[i].weight << " " << bag1.candies_in_bag[i].value << endl;
    // }
    // cout << endl;
    //
    // cout << "Candy in Bag2: " << endl;
    // for (unsigned int i = 0; i < bag2.candies_in_bag.size(); i++) {
    //     cout << bag2.candies_in_bag[i].weight << " " << bag2.candies_in_bag[i].value << endl;
    // }
    // cout << endl;
    //
    // cout << "Candy in Bag3: " << endl;
    // for (unsigned int i = 0; i < bag3.candies_in_bag.size(); i++) {
    //     cout << bag3.candies_in_bag[i].weight << " " << bag3.candies_in_bag[i].value << endl;
    // }
    // cout << endl;

    return (bag1.totalVal + bag2.totalVal + bag3.totalVal);

}


int refined() {
    int best = 0;

    for (int i = 0; i < T; i++) {
        srand(time(NULL));
        shuffle();
        int greedVal = greedy();

        for (int i = 0; i < N; i++) {
            stored_candies[i] = false;
        }

        if (greedVal > best) {
            best = greedVal;
        }
    }
    return best;
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

    sort_tasty();
    int greed = greedy();
    cout << "Greedy: " << greed << endl;


    int refine = refined();
    cout << "Refinement: " << refine << endl;

    return 0;
}
