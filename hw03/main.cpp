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


int greedy_loop(Bag b) {
    for (int i = N - 1; i >= 0; i--) {
        if (b.weight + candies[i].weight < 2000 && stored_candies[i] != true) {
            b.weight += candies[i].weight;
            b.candies_in_bag.push_back(candies[i]);
            stored_candies[i] = true;
            b.totalVal += candies[i].value;
        }
    }
    return b.totalVal;
}



int greedy(vector<Bag> bags) {
    Bag bag1, bag2, bag3;
    bag1 = bags[0];
    bag2 = bags[1];
    bag3 = bags[2];


    int total = 0;
    total += greedy_loop(bag1);
    total += greedy_loop(bag2);
    total += greedy_loop(bag3);

    // for (int i = N - 1; i >= 0; i--) {
    //     if (bag1.weight + candies[i].weight < 2000 && stored_candies[i] != true) {
    //         bag1.weight += candies[i].weight;
    //         bag1.candies_in_bag.push_back(candies[i]);
    //         stored_candies[i] = true;
    //         bag1.totalVal += candies[i].value;
    //     }
    // }
    //
    // for (int i = N - 1; i >= 0; i--) {
    //     if (bag2.weight + candies[i].weight < 2000 && stored_candies[i] != true) {
    //         bag2.weight += candies[i].weight;
    //         bag2.candies_in_bag.push_back(candies[i]);
    //         stored_candies[i] = true;
    //         bag2.totalVal += candies[i].value;
    //     }
    // }
    //
    // for (int i = N - 1; i >= 0; i--) {
    //     if (bag3.weight + candies[i].weight < 2000 && stored_candies[i] != true) {
    //         bag3.weight += candies[i].weight;
    //         bag3.candies_in_bag.push_back(candies[i]);
    //         stored_candies[i] = true;
    //         bag3.totalVal += candies[i].value;
    //     }
    // }

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

    return (total);

}


void shuffle_candies(vector<Bag> bags) {
    bags[0].clear();
    bags[1].clear();
    bags[2].clear();

    int j = 0;
    for (int i = 0; i < N; i++) {
        int temp = rand() % (i + 1);
        bags[rand() % 3].candies_in_bag.push_back(candies[i]);
    }
}



int refined(vector<Bag> bags) {
    Bag bag1, bag2, bag3;
    bag1 = bags[0];
    bag2 = bags[1];
    bag3 = bags[2];
    int best = 0;

    for (int i = 0; i < T; i++) {
        srand(time(NULL));
        shuffle_candies(bag1, bag2, bag3);
        int greedVal = greedy(bags);

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


    int refine = refined(mainBags);
    cout << "Refinement: " << refine << endl;

    return 0;
}
