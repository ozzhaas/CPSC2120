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
        string sub = temp.substr(31, ' ');
        int num = sub.find(' ');
        cout << num << endl;
        cout << sub << " ";
        // cout << end << endl;

    }






















    return 0;
}
