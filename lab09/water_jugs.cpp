/*Kellen Haas
  CPSC 2120
  lab09
  11/13/2020
*/

#include <iostream>
#include <stdio.h>

const int N = 1001; //Maximum that the max capacity of either jug can be
int X; //X is the goal units of water in the jugs combined
bool visited[N][N];
char marked[N][N];


struct Jug {
    int full; //Equivalent to 'A' for first jug and 'B' for second jug
    int curr; //Equivalent to 'a' for first jug and 'b' for second jug
};

Jug jug1, jug2;
jug1.full = A;
jug2.full = B;

bool visit(Jug j1, Jug j2, string prev) {
    if (j1.curr < 0 || j2.curr < 0 || j1.curr > N-1 || j2.curr > N-1) {
        return false;
    }

    if (visited[j1.curr][j2.curr]) {
        return false;
    }

    visited[j1.curr][j2.curr] = true;

    if (j1.curr + j2.curr == X) {
        visited[j1.curr][j2.curr] = true;
        return true;
    }

    //State(A, b) jug 1 is filled//
    if (visit(j1.full, j2.curr, "Fill jug 1")) {
        marked[j1.curr][j2.curr] = 1; //1 for filling jug1
        return true;
    }

    //State(0, b) jug 1 is emptied//
    if (visit(0, j2.curr, "Empty jug 1")) {
        marked[j1.curr][j2.curr] = 2; //2 for emptying jug1
        return true;
    }

    //State(a, B) jug 2 is filled//
    if (visit(j1.curr, j2.full, "Fill jug 2")) {
        marked[j1.curr][j2.curr] = 3; //3 for filling jug2
        return true;
    }

    //State(a, 0) jug 2 is emptied//
    if (visit(j1.curr, 0, "Empty jug 2")) {
        marked[j1.curr][j1.curr] = 4; //4 for emptying jug2
        return true;
    }

    //State(0, a + b) or ((a + b)-B, B) jug 1 is poured into jug 2//
    if (visit(0, j1.curr + j2.curr, "Pour 1 -> 2") || visit((j1.curr + j2.curr) - j2.full, j2.full, "Pour 1 -> 2")) {
        marked[j1.curr][j2.curr] = 5; //5 for pouring jug1 into jug2
        return true;
    }

    //State(a + b, 0) or (B, (a + b)-B) jug 2 is poured into jug 1//
    if (visit(j1.curr + j2.curr, 0, "Pour 2 -> 1") || visit(j2.full, (j1.curr + j2.curr) - j2.full, "Pour 2 -> 1")) {
        marked[j1.curr][j2.curr] = 6; //6 for pouring jug2 into jug1
        return true;
    }
    return false;
}


void print_transitions(int x, int y) {
    int finalState = marked[jug1.curr][jug2.curr];

    switch(finalState) {
        case 1:
            cout << "Fill jug 1  [a = " << jug1.full << ", b = " << y << "]\n";
            print_transitions(jug1.full, y);
            break;
        case 2:
            cout << "Empty jug 1  [a = " << 0 << ", b = " << y << "]\n";
            print_transitions(0, y);
            break;

        case 3:
            cout << "Fill jug 2  [a = " << x << ", b = " << jug2.full << "]\n";
            print_transitions(x, jug2.full);
            break;

        case 4:
            cout << "Empty jug 2  [a = " << x << ", b = " << 0 << "]\n";
            print_transitions(x, 0);
            break;

        case 5:
            //State (0, a + b)
            if (x == 0 && y == jug1.curr + jug2.curr) {
                cout << "Pour 1 -> 2 [a = " << 0 << ", b = " << jug1.curr + jug2.curr << "]\n";
                print_transitions(0, j1.curr + j2.curr);
            }
            //State ((a+b) - B, B)
            else if (x == (jug1.curr + jug2.curr) - jug2.full && y == jug2.full) {
                cout << "Pour 1 -> 2 [a = " << (jug1.curr + jug2.curr) - jug2.full << ", b = " << jug2.full << "]\n";
                print_transitions((j1.curr + j2.curr) - j2.full, j2.full);
            }
            break;

        case 6:
            //State (0, a + b)
            if (y == 0 && x == jug1.curr + jug2.curr) {
                cout << "Pour 2 -> 1 [a = " << jug1.curr + jug2.curr << ", b = " << 0 << "]\n";
                print_transitions(j1.curr + j2.curr, 0);
            }
            //State ((a+b) - B, B)
            else if (x == j2.full && y == (jug1.curr + jug2.curr) - jug2.full) {
                cout << "Pour 2 -> 1 [a = " << j2.full << ", b = " << (jug1.curr + jug2.curr) - jug2.full << "]\n";
                print_transitions(j2.full, (jug1.curr + jug2.curr) - jug2.full);
            }
            break;
        }
}


int main () {
    int A, B; //Big A and Big B are the max capacity for jugs 1 and 2 respectively
    Jug mJug1, mJug2;
    mJug1.curr = 0;
    mJug2.curr = 0;

    cout << "Enter A: ";
    cin >> A;
    cout << endl;
    cout << "Enter B: ";
    cin >> B;
    cout << endl;
    cout << "Enter X: ";
    cin >> X;
    cout << endl << endl;

    mJug1.full = A;
    mJug2.full = B;

    print_transitions(mJug1.curr, mJug2.curr);


    return 0;
}
