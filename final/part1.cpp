#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;



int main (void) {
    string temp;

    ifstream input;
    input.open("tf.txt");

    while (getline(input, temp)) {
        unsigned numPos = temp.find("question");
        string num = temp.at(numPos);
        size_t pos = temp.find("is");
        string end = temp.substr(pos + 3);
        cout << num << " ";
        cout << end << endl;

    }






















    return 0;
}
