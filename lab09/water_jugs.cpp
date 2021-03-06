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

struct State {
    bool beenthere;
    int pred_a, pred_b;
    const char *pred_string;
} S[1001][1001];



void visit(int a, int b, int pred_a, int pred_b, const char *pred_string) {

    if (S[a][b].beenthere) {return;}
    State s = {true, pred_a, pred_b, pred_string};
    S[a][b] = s;

    visit(A, b, a, b, "Fill jug 1\t\t");
    visit(a, B, a, b, "Fill jug 2\t\t");
    visit(0, b, a, b, "Empty jug 1\t\t");
    visit(a, 0, a, b, "Empty jug 2\t\t");

    int pour_quantity = min(a, B-b);
    visit(a - pour_quantity, b + pour_quantity, a, b, "Pour jug1->jug2\t\t");
    pour_quantity = min(b, A-a);
    visit(a + pour_quantity, b - pour_quantity, a, b, "Pour jug2->jug1\t\t");
}


void print_transitions(int a, int b) {
    if (a + b != 0) {
        print_transitions(S[a][b].pred_a, S[a][b].pred_b);
    }
    cout << S[a][b].pred_string << " [a = " << a << ", " << "b = " << b << "]\n";

}


int main () {
    cout << "Enter jug1's size: ";
    cin >> A;
    cout << endl;
    cout << "Enter jug2's size: ";
    cin >> B;
    cout << endl;
    cout << "Enter target amount: ";
    cin >> X;
    cout << endl << endl;

    visit(0, 0, 0, 0, "Starting point\t\t");

    for (int i = 0; i <= X; i++) {
        if (S[i][X-i].beenthere) {
            print_transitions(i, X - i);
            return 0;
        }
    }
    cout << "No solution!\n";

    return 0;
}
