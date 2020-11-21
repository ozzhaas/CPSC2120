/*Kellen Haas
  CPSC 2120
  Lab10
  11/20/20
*/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <fstream>
#include <ctype.h>
#include "stringIntMap.h"

using namespace std;


typedef string Node;
StringIntMap stringSet;
vector<string> solution;
vector<string> solFinal;

vector<Node> all_nodes;
map<Node, int> dist;
vector<int> distValues;
map<Node, Node> pred;
map<Node, vector<Node>> neighbors;



void readStartandEnd(Node &startNode, Node &endNode) {
    char userInput;
    string s, d; //s for start, d for destination

    cout << "Enter the word you want to start with: \n";
    cin >> s;
    cout << "Enter the word you want to end with: \n";
    cin >> d;
    cout << "Want me to find the shortest path or word ladder from "
            + s + " to " + d + " ? (\"Y\" for yes or \"N\" for no.)";
    cin >> userInput;
    userInput = toupper(userInput);
    while (userInput == 'N') {
        cout << "Re-enter the word you want to start with: \n";
        cin >> s;
        cout << "Re-enter the word you want to end with: \n";
        cin >> d;
        cout << "Want me to find the shortest path or word ladder from "
                + s + " to " + d + " ? (\"Y\" for yes or \"N\" for no.)";
        cin >> userInput;
        userInput = toupper(userInput);
    }
    startNode = s;
    endNode = d;
}




void adjacencyList(Node &startNode, Node &endNode) {
    char letter;
    for (auto word : all_nodes) {
        vector<Node> changeOneLetter;
        string oldWord = word;
        for (unsigned int i = 0; i < word.size(); i++) {
            letter = word[i];
            for(int j = 97; j < 122; j++) {
                word[i] = j;
                if (stringSet.find(word) && word != oldWord) {
                    changeOneLetter.push_back(word);
                }
            }
            word[i] = letter;
        }
    neighbors.insert(make_pair(word, changeOneLetter));
    }
}



void breadth_first(Node &src, Node &dest) {

    for (Node &a : all_nodes) {
        dist[a] == all_nodes.size();
    }

    dist[src] = 0;
    queue<Node> to_visit;
    to_visit.push(src);

    while (!to_visit.empty()) {
        Node x = to_visit.front();
        to_visit.pop();
        for (Node n : neighbors[x]) {
            if (dist[n] == all_nodes.size()) {
                distance[n] = 1 + distance[x];
                pred[n] = x;
                to_visit.push(n);
            }
        }
    }
}


int findLongestLadder(Node &startNode, Node &endNode) {
    vector<Node> beenthere;
    queue<Node> to_visit;
    int longest = 0;
    int num = 0;
    dist.clear();
    pred.clear();
    solution.clear();


    for (Node word : all_nodes) {
        string tempWord = breadth_first(word);
        num = dist[tempWord];
        if (num > longest) {
            printLadderPath(word, tempWord);
            solFinal = solution;
            longest = num;
        }
        distValues.push_back(num);

        dist.clear();
        pred.clear();
        solution.clear();
    }

    for (Node w : solFinal) {
        cout << w << endl;
    }

    return 0;
}


int printLadderPath(Node &startNode, Node &endNode) {
    int var = 0;

    if (startNode != endNode) {
        finalSol.push_back(pred[endNode]);
        printLadderPath(startNode, pred[endNode]);
        var = findLongestLadder();
    }
    cout << var << endl;
    return var;
}


int main () {
    Node startNode;
    Node endNode;
    string mainWord;
    int count = 0;
    ifstream input;

    input.open("words5.txt");
    while (input >> mainWord) {
        stringSet.insert(mainWord, count);
        all_nodes.push_back(mainWord);
        count++;
    }

    input.close();


    readStartandEnd(startNode, endNode);
    adjacencyList(startNode, endNode);
    int temp = findLongestLadder(startNode, endNode);
    printLadderPath(startNode, endNode);

    cout << "Distance = " << temp << endl;




    return 0;
}
