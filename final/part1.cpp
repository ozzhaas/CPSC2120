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
        size_t pos = temp.find("is");
        string end = temp.substr(pos + 3);
        size_t numPos = temp.find("question");
        string num = temp.substr(numPos + 9, " ");
        string garbage = temp.substr(numPos + 9);
        cout << num << " ";
        cout << end << endl;

    }






















    return 0;
}
