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

    while (getline(input, temp)) {
        // size_t pos = temp.find("question");
        string number = temp.substr(temp.find_last_of(' ', 29, 1), 3);

        // size_t num = temp.find("is");
        // string number = temp.substr(pos + 9, ' ');
        char TorF = temp.back();
        cout << number << " ";
        cout << TorF << endl;
    }



















    return 0;
}
