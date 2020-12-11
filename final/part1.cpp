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
        size_t pos = temp.find("question");
        string sub = temp.substr(pos + 9, ' ');
        char TorF = temp.back();
        cout << sub << " ";
        cout << TorF << endl;
    }



















    return 0;
}
