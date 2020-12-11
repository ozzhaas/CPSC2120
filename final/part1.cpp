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
        size_t F = temp.find('F');
        size_t T = temp.find('T');
        string fString = temp.substr(F);
        string tString = temp.substr(T);
        string sub = temp.substr(31, ' ');
        size_t num = sub.find(' ');
        string number = sub.substr(0, num);
        cout << number << " ";
        cout << fString << tString << endl;
    }



















    return 0;
}
