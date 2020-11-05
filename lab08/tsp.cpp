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

/*Total Number of Cities*/
const int N = 50;

/*Struct of Points that have an x and y coordinate*/
struct Point {
    double x, y;
    int index;
};

/*Create an array of Points of size N*/
Point P[N];


/*Basic function to calculate the distance of a side using Pythagorean Theorem*/
double dist(int a, int b) {
    double dx = P[a].x - P[b].x;
    double dy = P[a].y - P[b].y;
    return sqrt((dx * dx) + (dy * dy));
}


/*Calculate the total length of the tour*/
double tour_length(int* T) {
    double total = 0.0;
    for (int i = 0; i < N; i++) {
        int a = T[i];
        int b = T[(i + 1) % N];
        total += dist(a, b);
    }
    return total;
}

/*Shuffles the contents of or points in the tour array*/
void make_rand(int* T) {
    for (int i = 0; i < N; i++) {
        T[i] = i;
        swap(T[i], T[rand() % (i + 1)]);
    }
}

/*Swaps the values in the array at a position and a randomly-chosen preceding position*/
void substitute(int* T, int a, int b) {
    //Base Case
    if (a >= b) {return;}

    swap(T[a], T[b]);
    //Recursively swap the rest of the contents of the array
    substitute(T, a + 1, b - 1);
}

/* Refines the tour to find the optimal-local tour*/
bool refine_tour(int* T) {
    //Store the original length of the tour//
    double og_len = tour_length(T);

    //Loop through the entire array//
    for (int i = 0; i < N; i++) {
        //Loop through the array to get positions i + 2//
        for (int j = i + 2; j < N; j++) {
            //Call substitute to swap the positions accordingly//
            substitute(T, i + 1, j);

            /*If the original length is greater than the current tour's length
              then the tour has been refined*/
            if (tour_length(T) < og_len) {
                return true;
            }
            /*Otherwise keep refining*/
            substitute(T, i + 1, j);
        }
    }
    return false;
}



int main (void) {
    int tour[N];
    int best_tour[N];

    ifstream in;
    in.open("tsp_points.txt");

    for (int i = 0; i < N; i++) {
        in >> P[i].x >> P[i].y;
    }

    in.close();


    double best_num = 1000;

    for (int i = 0; i < N; i++) {
        srand(time(NULL));
        make_rand(tour);
        while (refine_tour(tour));

        double new_len = tour_length(tour);
        if (new_len < best_num) {
            best_num = new_len;
            for (int j = 0; j < N; j++) {
                best_tour[j] = tour[j];
            }
        }
    }

    cout << "Length of the most optimal tour: " << best_num << endl;
    cout << "~~~~~~~~~~~~~~~~~~~Path~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;

    for (int i = 0; i < N; i++) {
        cout << best_tour[i] << " ";
    }
    cout << endl << endl;

return 0;
}
