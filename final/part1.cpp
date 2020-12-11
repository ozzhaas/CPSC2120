#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

struct myLine {
    char trueOrFalse;
    int num;
};


int compareNums (const myLine &a, const myLine &b) {
    return a.num < b.num;
}


int main (void) {
    string temp;
    vector<myLine> vec;
    ifstream input;
    input.open("tf.txt");
    ofstream output;
    output.open("answers.txt");
    string line;

    while (getline(input, temp)) {
        size_t pos = temp.find("question");
        string number = temp.substr(temp.find_last_of(' ', pos + 9), 4);
        char TorF = temp.back();
        int line_number = stoi(number);
        myLine outLine;
        outLine.num = line_number;
        outLine.trueOrFalse = TorF;
        vec.push_back(outLine);
        sort(vec.begin(), vec.end(), compareNums);
    }


    for (unsigned int i = 0; i < vec.size(); i++) {
        output << vec[i].trueOrFalse << endl;
    }

    return 0;
}
