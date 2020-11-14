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


bool can_visit(int x, int y) {
    cout << "TEST\n";
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
    if (can_visit(A, y) && !visited[A][y]) {
        visited[A][y] = true;
        marked = 1; //1 for filling jug1
        prevStep[marked] = "Fill jug 1";
        return true;
    }

    // //State(0, b) jug 1 is emptied//
    // if (can_visit(0, y) && !visited[0][y]) {
    //     visited[0][y] = true;
    //     marked = 2; //2 for emptying jug1
    //     prevStep[marked] = "Empty jug 1";
    //     return true;
    // }
    //
    // //State(a, B) jug 2 is filled//
    // if (can_visit(x, B) && !visited[x][B]) {
    //     visited[x][B] = true;
    //     marked = 3; //3 for filling jug2
    //     prevStep[marked] = "Fill jug 2";
    //     return true;
    // }
    //
    // //State(a, 0) jug 2 is emptied//
    // if (can_visit(x, 0) && !visited[x][0]) {
    //     visited[x][0] = true;
    //     marked = 4; //4 for emptying jug2
    //     prevStep[marked] = "Empty jug 2";
    //     return true;
    // }
    //
    // //State(0, a + b) jug 1 is poured into jug 2//
    // if (can_visit(0, x + y) && !visited[0][x + y]) {
    //     visited[0][x + y] = true;
    //     marked = 5; //5 for pouring jug1 into jug2
    //     prevStep[marked] = "Pour 1 -> 2";
    //     return true;
    // }
    // //State((a + b)-B, B) jug 1 is poured into jug 2//
    // if (can_visit((x + y) - B, B) && !visited[(x + y) - B][B]) {
    //     visited[(x + y) - B][B] = true;
    //     marked = 6; //5 for pouring jug1 into jug2
    //     prevStep[marked] = "Pour 1 -> 2";
    //     return true;
    // }
    //
    // //State(a + b, 0) jug 2 is poured into jug 1//
    // if (can_visit(x + y, 0) && !visited[x + y][0]) {
    //     visited[x + y][0] = true;
    //     marked = 7; //6 for pouring jug2 into jug1
    //     prevStep[marked] = "Pour 2 -> 1";
    //     return true;
    // }
    //
    // //State(B, (a + b)-B) jug 2 is poured into jug 1//
    // if (can_visit(B, (x + y) - B) && !visited[B][(x + y) - B]) {
    //     visited[B][(x + y) - B] = true;
    //     marked = 8; //6 for pouring jug2 into jug1
    //     prevStep[marked] = "Pour 2 -> 1";
    //     return true;
    // }

    return false;
}


void print_transitions(int x, int y) {
    int finalState = marked;
    switch(finalState) {
        case 1:
            cout << prevStep[marked] << "  [a = " << A << ", b = " << y << "]\n";
            print_transitions(A, y);
            break;
        case 2:
            cout << prevStep[marked] << "  [a = " << 0 << ", b = " << y << "]\n";
            print_transitions(0, y);
            break;

        case 3:
            cout << prevStep[marked] << "  [a = " << x << ", b = " << B << "]\n";
            print_transitions(x, B);
            break;

        case 4:
            cout << prevStep[marked] << "  [a = " << x << ", b = " << 0 << "]\n";
            print_transitions(x, 0);
            break;

        case 5:
            //State (0, a + b)
            cout << prevStep[marked] << "  [a = " << 0 << ", b = " << x + y << "]\n";
            print_transitions(0, x + y);
            break;

        case 6:
            //State ((a+b) - B, B)
            cout << prevStep[marked] << "  [a = " << (x + y) - B << ", b = " << B << "]\n";
            print_transitions((x + y) - B, B);
            break;

        case 7:
            //State (0, a + b)
            cout << prevStep[marked] << "  [a = " << x + y << ", b = " << 0 << "]\n";
            print_transitions(x + y, 0);
            break;

        case 8:
            //State ((a+b) - B, B)
            cout << prevStep[marked] << "  [a = " << A << ", b = " << (x + y) - B << "]\n";
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

    int a = 0;
    int b = 0;

    if (can_visit(a, b)){
        print_transitions(a, b);
    }
    else {
        cout << "Impossible!\n";
    }

    return 0;
}
