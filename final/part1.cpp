#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

struct numTorF {
    int num = 0;
    char TorF;
};



int main (void) {
    numTorF questions;
    string temp;
    vector<char> vec;
    ifstream input;
    input.open("tf.txt");
    string num;
    char TorF;

    int i = 0;
    while (getline(input, temp)) {
        input >> temp;
        input >> temp;
        input >> temp;
        input >> temp;
        input >> temp;
        input >> temp;
        input >> num;
        string tempNum = stoi(num);
        questions.num = tempNum;
        input >> temp;
        input >> TorF;
        questions.TorF = TorF;
        cout << questions.num << " " << questions.TorF << endl;
    }



















    return 0;
}
