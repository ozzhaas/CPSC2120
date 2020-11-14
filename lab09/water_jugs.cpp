/*Kellen Haas
  CPSC 2120
  lab09
  11/13/2020
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <string>

using namespace std;

const int N = 1001; //Maximum that the max capacity of either jug can be
int A, B; //Big A and Big B are the max capacity for jugs 1 and 2 respectively
int X; //X is the goal units of water in the jugs combined
bool visited[N][N];
char marked[N][N];


struct Jug {
    int full; //Equivalent to 'A' for first jug and 'B' for second jug
    int curr; //Equivalent to 'a' for first jug and 'b' for second jug
};


bool visit(int x, int y, string prev) {

    if (x < 0 || y < 0 || x > N-1 || y > N-1) {
        return false;
    }

    if (visited[x][y]) {
        return false;
    }

    visited[x][y] = true;

    if (x + y == X) {
        visited[x][y] = true;
        return true;
    }

    //State(A, b) jug 1 is filled//
    if (visit(A, y, "Fill jug 1")) {
        marked[x][y] = 1; //1 for filling jug1
        return true;
    }

    //State(0, b) jug 1 is emptied//
    if (visit(0, y, "Empty jug 1")) {
        marked[x][y] = 2; //2 for emptying jug1
        return true;
    }

    //State(a, B) jug 2 is filled//
    if (visit(x, B, "Fill jug 2")) {
        marked[x][y] = 3; //3 for filling jug2
        return true;
    }

    //State(a, 0) jug 2 is emptied//
    if (visit(x, 0, "Empty jug 2")) {
        marked[x][y] = 4; //4 for emptying jug2
        return true;
    }

    //State(0, a + b) or ((a + b)-B, B) jug 1 is poured into jug 2//
    if (visit(0, x + y, "Pour 1 -> 2") || visit((x + y) - B, B, "Pour 1 -> 2")) {
        marked[x][y] = 5; //5 for pouring jug1 into jug2
        return true;
    }

    //State(a + b, 0) or (B, (a + b)-B) jug 2 is poured into jug 1//
    if (visit(x + y, 0, "Pour 2 -> 1") || visit(B, (x + y) - B, "Pour 2 -> 1")) {
        marked[x][y] = 6; //6 for pouring jug2 into jug1
        return true;
    }
    return false;
}


void print_transitions(int x, int y) {
    int finalState = marked[x][y];
    cout << "TEST\n";
    switch(finalState) {
        case 1:
            cout << "Fill jug 1  [a = " << A << ", b = " << y << "]\n";
            print_transitions(A, y);
            break;
        case 2:
            cout << "Empty jug 1  [a = " << 0 << ", b = " << y << "]\n";
            print_transitions(0, y);
            break;

        case 3:
            cout << "Fill jug 2  [a = " << x << ", b = " << B << "]\n";
            print_transitions(x, B);
            break;

        case 4:
            cout << "Empty jug 2  [a = " << x << ", b = " << 0 << "]\n";
            print_transitions(x, 0);
            break;

        case 5:
            //State (0, a + b)
            if (x == 0 && y == x + y) {
                cout << "Pour 1 -> 2 [a = " << 0 << ", b = " << x + y << "]\n";
                print_transitions(0, x + y);
            }
            //State ((a+b) - B, B)
            else if (x == (x + y) - B && y == B) {
                cout << "Pour 1 -> 2 [a = " << (x + y) - B << ", b = " << B << "]\n";
                print_transitions((x + y) - B, B);
            }
            break;

        case 6:
            //State (0, a + b)
            if (y == 0 && x == x + y) {
                cout << "Pour 2 -> 1 [a = " << x + y << ", b = " << 0 << "]\n";
                print_transitions(x + y, 0);
            }
            //State ((a+b) - B, B)
            else if (x == A && y == (x + y) - B) {
                cout << "Pour 2 -> 1 [a = " << A << ", b = " << (x + y) - B << "]\n";
                print_transitions(A, (x + y) - B);
            }
            break;
        }
}


int main () {
    cout << "Enter A: ";
    cin >> A;
    cout << endl;
    cout << "Enter B: ";
    cin >> B;
    cout << endl;
    cout << "Enter X: ";
    cin >> X;
    cout << endl << endl;

    int a = 0, b = 0;

    print_transitions(a, b);


    return 0;
}
