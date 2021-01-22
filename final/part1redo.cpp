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

const int size = 1000000;


struct Node {
    char trueOrFalse;
    int freq;
    Node *next;
    Node (char t, int f, Node *n) { trueOrFalse = t; freq = f; next = n; }
};

int myhash(char t, int f, int table_size)
{
  unsigned int i, h = 0;
  for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)t[i]) % table_size;
  return h;
}


int compareNums (const myLine &a, const myLine &b) {
    return a.num < b.num;
}



int main () {
    Node *head;
    head = new Node *[size];
    for (int i = 0; i < size; i++) {head[i] = NULL;}
    int frequency = 0;
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
        int h = myhash(TorF, frequency, size);
        head[h] = new Node(TorF, frequency, head[h]);
        int line_number = stoi(number);

    }
    return 0;
}
















}
