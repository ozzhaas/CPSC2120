/*Kellen Haas
  CPSC 2120
  Lab07
  10/22/2020
*/



#include <iostream>
#include <iomanip>

using namespace std;

int N, half;
int **board;
int count;
bool oddBall = false;
bool even = false;


bool check_pos(int r, int c) {
    int row = r;
    int col = c;
    // 
    // int leftdiag[N];
    // int rightdiag[N];
    // int column[N];


/*******************Second Solution...May Be Faster?*******************/
    // for (int i = 0; i < N; i++) {
    //     if ((leftdiag[i - c + N - 1] != 1 && rightdiag[i + c] != 1) && column[i] != 1) {
    //         board[i][c] = 1;
    //         leftdiag[i - c + N - 1] = rightdiag[i + c] = column[i] = 1;
    //         if (check_pos(r, c + 1)) {return true;}
    //         board[i][c] = 0;
    //         leftdiag[i - c + N - 1] = rightdiag[i + c] = column[i] = 0;
    //     }
    // }
    // return false;



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

    for (row = r - 1, col = c + 1; col < N && row >= 0; row--, col++) {
        if (board[row][col]) {
            return false;
        }
    }

    return true;
}


void check_row(int r) {

    if (r == N) {
        count += 2;
        if (even) {
            count - 1;
        }
        return;
    }
    if (r != 0) {
        for (int col = 0; col < N; col++) {
            if (check_pos(r, col)) {
                board[r][col] = true;
                check_row(r + 1);
                board[r][col] = false;
            }
        }
    }
    else if (N % 2 == 0) {
        for (int col = 0; col < N/2; col++) {
            if (check_pos(r, col)) {
                board[r][col] = true;
                check_row(r + 1);
                board[r][col] = false;
            }
        }
    }
    else {
        for (int col = 0; col < (N/2) + 1; col++) {
            if (col == N/2) {
                even = true;
            }
            if (check_pos(r, col)) {
                board[r][col] = true;
                check_row(r + 1);
                board[r][col] = false;
            }
        }
    }
}



int main(int argc, char* argv[]) {

    N = atoi(argv[1]);

    board = new int* [N];
    for (int i = 0; i < N; i++) {
        board[i] = new int[N];
    }
    check_row(0);


    cout << "Total Number of Solutions: " << count << endl;


    return 0;
}
