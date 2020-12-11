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
        size_t is = sub.find("is");
        string garbage = temp.substr(30, is);
        for (int i = 0; i < sizeof(garbage); i++) {
            vec.push_back(i);
        }
        cout << number << " ";
        cout << vec[vec.size()] << endl;
        // cout << end << endl;

    }






















    return 0;
}
