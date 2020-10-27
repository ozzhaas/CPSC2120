/*Kellen Haas
  CPSC 2120
  Lab07
  10/22/2020
*/



#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

int N, half;
int **board;
int count;



bool check_pos(int r, int c) {
    int row = r;
    int col = c;

    for (int i = r - 1; i >= 0; i--) {
        if (board[i][c]) {
            return false;
        }
    }

    for (row = r - 1, col = c - 1; row >= 0 && col >= 0; row--, col--) {
        if (board[row][col]) {
            return false;
        }
    }

    for (row = r - 1, col = c + 1; row >= 0 && col < N; row--, col++) {
        if (board[row][col]) {
            return false;
        }
    }

    return true;
}


void check_row(int r) {
    if (r == N) {
        count++;
        return;
    }
    for (int i = 0; i < N; i++) {
        if (check_pos(r, i)) {
            board[r][i] = true;
            check_row(r + 1);
            board[r][i] = false;
        }
    }
}






/*Checks the number of command line arguments*/
bool checkArgs(int argc){
    if (argc != 2) {
        cout << "No input file provided. Try again.\n";
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {

    N = atoi(argv[1]);
    bool oddBall = false;

    half = N/2;
    oddBall = N % 3;
    if (oddBall) {
        half = (N/2) + oddBall;
    }


    if (checkArgs(argc)) {
        board = new int* [N];
        for (int i = 0; i < N; i++) {
            board[i] = new int[N];
        }
        check_row(0);
    }


    cout << "Total Number of Solutions: " << count << endl;


    return 0;
}
