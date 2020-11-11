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

struct Bag {
    int weight = 0;
    int totalVal = 0;
    vector<Candy> candies_in_bag;
};

const int N = 16;
const int T = 1000;
Candy candies[N];
int maxWeight = 2000;
bool stored_candies[N];





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


int greedy_loop(Bag &b) {
    for (int i = N - 1; i >= 0; i--) {
        if (b.weight + candies[i].weight <= 2000 && stored_candies[i] != true) {
            b.weight += candies[i].weight;
            b.candies_in_bag.push_back(candies[i]);
            stored_candies[i] = true;
            b.totalVal += candies[i].value;
        }
    }
    return b.totalVal;
}



int greedy(vector<Bag> &bags) {
    Bag bag1, bag2, bag3;
    bag1 = bags[0];
    bag2 = bags[1];
    bag3 = bags[2];


    int total = 0;
    total += greedy_loop(bag1);
    total += greedy_loop(bag2);
    total += greedy_loop(bag3);

    return (total);

}


void shuffle_candies(vector<Bag> &bags) {
    // for (int i = 0; i < N; i++) {
    int i = 0;
    while (bags[random].weight < 2000 && !stored_candies[i]) {
        int random = rand() % 3;
        if (bags[random].weight >= 2000) {break;}
        bags[random].weight += candies[i].weight;
        bags[random].candies_in_bag.push_back(candies[i]);
        stored_candies[i] = true;
        bags[random].totalVal += candies[i].value;
        i++;
    }

        // if (bags[random].weight + candies[i].weight <= 2000 && stored_candies[i] != true) {
        //
        //     // cout << "Adding candies[" << i << "]: " << endl;
        //     // cout << "candies[" << i << "].weight = " << candies[i].weight << endl;
        //     // cout << "candies[" << i << "].value = " << candies[i].value << endl;
        //
        //     bags[random].weight += candies[i].weight;
        //     bags[random].candies_in_bag.push_back(candies[i]);
        //     stored_candies[i] = true;
        //     bags[random].totalVal += candies[i].value;
        // }

    //}
}



int refined(vector<Bag> &bags) {
    Bag bag1, bag2, bag3;
    bag1 = bags[0];
    bag2 = bags[1];
    bag3 = bags[2];
    int best = 0;
    int total = 0;

    int j = rand() % 3;
    for (int i = 0; i < T; i++) {
        shuffle_candies(bags);
        total = bags[0].totalVal + bags[1].totalVal + bags[2].totalVal;
        if (total > best) {
            cout << endl << endl << "TEST TOTAL IN REFINED FUNC: " << total << endl << endl;
            best = total;
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
    vector<Bag> mainBags;
    Bag bag1, bag2, bag3;

    mainBags.push_back(bag1);
    mainBags.push_back(bag2);
    mainBags.push_back(bag3);


    while (input >> tempVar) {
        Candy tempCandy;
        tempCandy.weight = tempVar;
        input >> tempVar;
        tempCandy.value = tempVar;
        candies[i] = tempCandy;
        i++;
    }

    sort_tasty();
    int greed = greedy(mainBags);
    cout << "Greedy: " << greed << endl;


    //Clear bag contents
    mainBags[0].candies_in_bag.clear();
    mainBags[1].candies_in_bag.clear();
    mainBags[2].candies_in_bag.clear();

    //Clear array of stored "used" candies
    for (int i = 0; i < N; i++) {
        stored_candies[i] = false;
    }

    int refine = refined(mainBags);
    cout << "Refinement: " << refine << endl;

    cout << endl << endl;
    cout << "~~~~~~~~~~~~~~~~Weights~~~~~~~~~~~~~~~~" << endl;
    cout << "Bag1 weight: " << mainBags[0].weight << endl;
    cout << "Bag2 weight: " << mainBags[1].weight << endl;
    cout << "Bag3 weight: " << mainBags[2].weight << endl;

    cout << endl << endl;
    cout << "~~~~~~~~~~~~~~~~Values~~~~~~~~~~~~~~~~" << endl;
    cout << "Bag1 value: " << mainBags[0].totalVal << endl;
    cout << "Bag2 value: " << mainBags[1].totalVal << endl;
    cout << "Bag3 value: " << mainBags[2].totalVal << endl;



    return 0;
}
