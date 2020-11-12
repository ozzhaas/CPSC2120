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
int best = 0;



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

void add_to_bag(Bag &b, int i) {
    if (b.weight + candies[i].weight <= 2000 && stored_candies[i] != true) {
        b.weight += candies[i].weight;
        b.candies_in_bag.push_back(candies[i]);
        stored_candies[i] = true;
        b.totalVal += candies[i].value;
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
    bool must_leave_out = false;

    for (int i = 0; i < N; i++) {
        int random = (rand() % 3) + 1;
        if (bags[random].weight + candies[i].weight > 2000 && stored_candies[i] != true) {
            must_leave_out = true;
            for (int j = 1; j < 4; j++) {
                add_to_bag(bags[j], i);
                must_leave_out = false;
            }
        if (must_leave_out) {bags[0].candies_in_bag.push_back(candies[i]);}
        }
        else {
            add_to_bag(bags[random], i);
        }
    }
}


int yummiest(Bag &b) {
    for (unsigned int i = 0; i < b.candies_in_bag.size(); i++) {
        int maximum = max(b.candies_in_bag[i].value, candies[i].value);
        return maximum;
    }
}



int refined(vector<Bag> &bags) {
    Bag bag1, bag2, bag3, storage_bag;
    storage_bag = bags[0];
    bag1 = bags[1];
    bag2 = bags[2];
    bag3 = bags[3];
    int total = 0;
    bool refine_me = true;

    for (int i = 0; i < T; i++) {
        refine_me = true;
        shuffle_candies(bags);
        best = bags[0].totalVal + bags[1].totalVal + bags[2].totalVal;
        while (refine_me == true) {
            refine_me = false;
            for (int j = 1; j < 4; j++) {
                for (unsigned int k = 0; k < bags[j].candies_in_bag.size(); k++) {
                    unsigned int random = k % bags[1].candies_in_bag.size();
                    bags[j].weight = bags[j].weight - bags[j].candies_in_bag[k].weight;
                    bags[j].weight += bags[j].candies_in_bag[random].weight;
                    bags[j].candies_in_bag[random].weight = bags[j].candies_in_bag[k].weight;

                    swap(bags[j].candies_in_bag[k], bags[j].candies_in_bag[random]);

                    int currYum = bags[1].totalVal + bags[2].totalVal + bags[3].totalVal;
                    int newYum = yummiest(bags[1]) + yummiest(bags[2]) + yummiest(bags[3]);
                    if (currYum > newYum) {
                        total = currYum;
                        refine_me = true;
                    }
                    else {
                        total = newYum;
                    }
                }
            }
        if (total > best) {best = total; refine_me = true;}
        else {refine_me = false;}
        }
    }
    cout << endl << endl << "TEST TOTAL IN REFINED FUNC: " << best << endl << endl;
    return best;
}


int pruned(vector<Bag> bags, int p) {
    int total = 0;
    if (p == N) {
        if (best > total) {
            total = best;
            return total;
        }
    }

    for (int i = 1; i < 4; i++) {
        add_to_bag(bags[i], p);
        total = pruned(bags, p + 1);
        best -= bags[i].candies[p].value;
        bags[i].weight -= bags[i].candies_in_bag[p].weight;
        stored_candies[p] = false;

        if (!stored_candies[p]) {
            bags[0].weight += bags[0].candies_in_bag[p].weight;
            stored_candies[p] = true;
            total = pruned(bags, p + 1);
            stored_candies[p] = false;
            bags[0].weight -= bags[0].candies_in_bag[p].weight;
        }

        if (best > total) {
            total = best;
        }
        else {best = total;}

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
    Bag bag1, bag2, bag3, storage_bag;

    mainBags.push_back(storage_bag);
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
    mainBags[3].candies_in_bag.clear();

    //Clear array of stored "used" candies
    for (int i = 0; i < N; i++) {
        stored_candies[i] = false;
    }

    int refine = refined(mainBags);
    cout << "Refinement: " << refine << endl;

    cout << endl << endl;
    cout << "~~~~~~~~~~~~~~~~Weights~~~~~~~~~~~~~~~~" << endl;
    cout << "Storage Bag weight: " << mainBags[0].weight << endl;
    cout << "Bag1 weight: " << mainBags[1].weight << endl;
    cout << "Bag2 weight: " << mainBags[2].weight << endl;
    cout << "Bag3 weight: " << mainBags[3].weight << endl;


    cout << endl << endl;
    cout << "~~~~~~~~~~~~~~~~Values~~~~~~~~~~~~~~~~" << endl;
    cout << "Storage Bag weight: " << mainBags[0].totalVal << endl;
    cout << "Bag1 value: " << mainBags[1].totalVal << endl;
    cout << "Bag2 value: " << mainBags[2].totalVal << endl;
    cout << "Bag3 value: " << mainBags[3].totalVal << endl;
    cout << endl << endl;

    int recursiveStart = 0;
    int prune = pruned(mainBags, 0);
    cout << "Exhaustive: " << prune << endl;

    return 0;
}
