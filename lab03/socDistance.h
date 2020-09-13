#ifndef SOCDISTANCE_H
#define SOCDISTANCE_H
#include <stdio.h>
#include <iostream>
#include <fstream>


using namespace std;


//set b to 1000 because program run time is big-O(n^2) and 1000^2 is 1,000,000
//which is the total number of coordinates in the text file.
const int b = 1000;
const int SIZE = 1000000

struct Coords {
    double x;
    double y;
};

struct Node {
  Coords p;
  Node *next;
  Node (Coords p2, Node *n) { p = p2; next = n; }
};


Node*** table[SIZE];

int myhash(Node***, int);

void allocate();

void deallocate();

void insert(Coords);

double find_distance(Point, Point);

double find_closest_cells(Node***);

double find_closest_coords(Point);














#endif
