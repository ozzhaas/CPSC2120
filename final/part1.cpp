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
    vector<char> vec;
    ifstream input;
    input.open("tf.txt");

    int i = 0;
    while (getline(input, temp)) {
        vec.push_back(temp.at(sizeof(temp)));
        string sub = temp.substr(31, ' ');
        size_t num = sub.find(' ');
        string number = sub.substr(0, num);
        cout << number << " ";
        cout << vec[i] << endl;
        i++;
    }



















    return 0;
}
