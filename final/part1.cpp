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
    vector<int> vec;
    ifstream input;
    input.open("tf.txt");

    while (getline(input, temp)) {
        string sub = temp.substr(31, ' ');
        size_t num = sub.find(' ');
        string number = sub.substr(0, num);


    }

    input.seekg(ios::beg);





















    return 0;
}
