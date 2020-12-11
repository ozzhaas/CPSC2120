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
    string line;

    int i = 0;
    while (getline(input, temp)) {
        size_t pos = temp.find(' ', 29);
        string sub = temp.substr(pos, ' ');
        size_t num = sub.find(' ');
        string number = sub.substr(0, num);
        size_t loc = sub.find("is");
        string TorF = sub.substr(loc, '\n');
        cout << number << " ";
        cout << TorF << endl;
    }



















    return 0;
}
