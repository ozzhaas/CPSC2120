/*Kellen Haas
  CPSC 2120
  Lab08
  10/29/2020
*/



#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>


using namespace std;


const int N = 50;

struct Point {
    double x, y;
    int index;
};

Point P[N];



double dist(int a, int b) {
    double dx = P[a].x - P[b].x;
    double dy = P[a].y - P[b].y;
    return sqrt((dx * dx) + (dy * dy));
}


double tour_length(int* T) {
    double total = 0.0;
    for (int i = 0; i < N; i++) {
        int a = T[i];
        int b = T[(i + 1) % N];
        total += dist(a, b);
    }
    return total;
}


void make_rand(int* T) {
    for (int i = 0; i < N; i++) {
        T[i] = i;
        swap(T[i], T[rand() % (i + 1)]);
    }
}


void substitute(int* T, int a, int b) {
    //Base Case
    if (a >= b) {return;}

    swap(T[a], T[b]);
    substitute(T, a + 1, b - 1);
}


bool refine_tour(int* T) {
    double og_len = tour_length(T);

    for (int i = 0; i < N; i++) {
        for (int j = i + 2; j < N; j++) {
            substitute(T, a + 1, b);
            if (tour_length(T) < og_len) {
                return true;
            }
            substitute(T, a + 1, b);
        }
    }
    return false;
}



int main (void) {
    int* tour[N];
    int* best;

    ifstream in;
    in.open("tsp_points.txt");

    for (itn i = 0; i < N; i++) {
        in >> P[i].x >> P[i].y;
    }

    in.close();


    double best_num = 9999999999999.9;
    for (int i = 0; i < N; i++) {
        tour[i] = i;
        swap(tour[i], tour[rand() % (i + 1)]);
    }

    while (refine_tour(tour));

    double new_len = tour_length(tour);
    if (new_len < best_num) {
        best_num = new_len;
        for (int i = 0; i < N; i++) {
            best[i] = tour[i];
        }
    }

    cout << "Length of the most optimal tour: " << best_num << endl;
    cout << "~~~~~~~~~~~~~~~~~~~Path~~~~~~~~~~~~~~~~~~~" << endl;

    for (int i = 0; i < N; i++) {
        cout << best[i] << " ";
    }
    cout << endl;

return 0;
}
