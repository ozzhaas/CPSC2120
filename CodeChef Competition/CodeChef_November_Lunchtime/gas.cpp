/*Kellen Haas
  CPSC 4890
  Coding Competition
  12/8/2020
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>


using namespace std;

void get_input(ifstream &input) {
    int N = 0;
    vector<int> fuel_level;

    input >> N;
    int cars[N][N];

    for (int i = 0; i < N; i++) {
        int tmp = 0;
        input >> tmp;
        fuel_level.push_back(tmp);
    }

    int traveled = 0;

    traveled += fuel_level[0];
    int leftover = fuel_level[0];

    int j = 1;
    //While your cars fuel is not empty
    //and the number of other cars is less than N
    while (leftover > 0 && j < N) {
        leftover--; //Subtract 1 from your gas level
                    //because you traveled one more space
        leftover += fuel_level[j]; //Steak gas from the next car you approach
        traveled += fuel_level[j];
        j++;
    }

    cout << traveled << endl;
}


int main () {
    int numTestCases = 0;

    ifstream input;
    input.open("gas.txt");
    char v, t;
    input >> numTestCases;

    cout << "NUMTESTCASES: " << numTestCases << endl;

    while(numTestCases--) {
        get_input(input);
    }

    return 0;


}
