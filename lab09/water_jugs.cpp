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
int marked;
string prevStep[10] = "start";


bool visit(int x, int y, string previous[10]) {
    string lastMove = "";
    if (x < 0 || y < 0 || x > N-1 || y > N-1) {
        return false;
    }

    if (visited[x][y]) {
        return false;
    }


    if (x + y == X) {
        visited[x][y] = true;
        return true;
    }

    //State(A, b) jug 1 is filled//
    lastMove = "Fill jug 1";
    if (visit(A, y, lastMove)) {
        visited[A][y] = true;
        marked = 1; //1 for filling jug1
        previous[marked] = lastMove;
        return true;
    }

    //State(0, b) jug 1 is emptied//
    lastMove = "Empty jug 1"
    if (visit(0, y, lastMove)) {
        visited[0][y] = true;
        marked = 2; //2 for emptying jug1
        previous[marked] = lastMove;
        return true;
    }

    //State(a, B) jug 2 is filled//
    lastMove = "Fill jug 2";
    if (visit(x, B, lastMove)) {
        visited[x][B] = true;
        marked = 3; //3 for filling jug2
        previous[marked] = lastMove;
        return true;
    }

    //State(a, 0) jug 2 is emptied//
    lastMove = "Empty jug 2";
    if (visit(x, 0, lastMove)) {
        visited[x][0] = true;
        marked = 4; //4 for emptying jug2
        previous[marked] = lastMove;
        return true;
    }

    //State(0, a + b) or ((a + b)-B, B) jug 1 is poured into jug 2//
    lastMove = "Pour 1 -> 2";
    if (visit(0, x + y, lastMove)) {
        visited[0][x + y] = true;
        marked = 5; //5 for pouring jug1 into jug2
        previous[marked] = lastMove;
        return true;
    }

    lastMove = "Pour 1 -> 2";
    if (visit((x + y) - B, B, lastMove)) {
        visited[(x + y) - B][B] = true;
        marked = 6; //5 for pouring jug1 into jug2
        previous[marked] = lastMove;
        return true;
    }

    //State(a + b, 0) or (B, (a + b)-B) jug 2 is poured into jug 1//
    lastMove = "Pour 2 -> 1";
    if (visit(x + y, 0, lastMove)) {
        visited[x + y][0] = true;
        marked = 7; //6 for pouring jug2 into jug1
        previous[marked] = lastMove;
        return true;
    }

    lastMove = "Pour 2 -> 1";
    if (visit(B, (x + y) - B, lastMove)) {
        visited[B][(x + y) - B] = true;
        marked = 8; //6 for pouring jug2 into jug1
        previous[marked] = lastMove;
        return true;
    }

    return false;
}


void print_transitions(int x, int y) {
    int finalState = marked;
    cout << finalState << endl;
    switch(finalState) {
        case 1:
            cout << previous[marked] "  [a = " << A << ", b = " << y << "]\n";
            print_transitions(A, y);
            break;
        case 2:
            cout << previous[marked] "  [a = " << 0 << ", b = " << y << "]\n";
            print_transitions(0, y);
            break;

        case 3:
            cout << previous[marked] "  [a = " << x << ", b = " << B << "]\n";
            print_transitions(x, B);
            break;

        case 4:
            cout << previous[marked] "  [a = " << x << ", b = " << 0 << "]\n";
            print_transitions(x, 0);
            break;

        case 5:
            //State (0, a + b)
            cout << previous[marked] "  [a = " << 0 << ", b = " << x + y << "]\n";
            print_transitions(0, x + y);
            break;

        case 6:
            //State ((a+b) - B, B)
            cout << previous[marked] "  [a = " << (x + y) - B << ", b = " << B << "]\n";
            print_transitions((x + y) - B, B);
            break;

        case 7:
            //State (0, a + b)
            cout << previous[marked] "  [a = " << x + y << ", b = " << 0 << "]\n";
            print_transitions(x + y, 0);
            break;

        case 8:
            //State ((a+b) - B, B)
            cout << previous[marked] "  [a = " << A << ", b = " << (x + y) - B << "]\n";
            print_transitions(A, (x + y) - B);
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

    if (visit(a, b, prevStep)){
        print_transitions(a, b);
    }
    else {
        cout << "Impossible!\n";
    }

    return 0;
}
