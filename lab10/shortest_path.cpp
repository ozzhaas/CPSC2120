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
#include "shortest_path.h"
#include "stringIntMap.h"

using namespace std;


int MAX_LEN = 999999;

WordLadder::WordLadder() {
    ifstream input;
    input.open("words5.txt");
    string in;
    int count;

    if (input.fail()) {
        cout << "Input file error.\n";
        return;
    }

    while(input >> in) {
        dict.insert(in, count);
        wordVec.push_back(in);
        count++;
    }

    input.close();
}


void WordLadder::readStartandEnd(Node &src, Node &dest) {
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
    src = s;
    dest = d;
}


void WordLadder::adjacencyList(StringIntMap &dict) {
    int length = 0;

    for (auto adjWord : wordVec) {
        vector<string> oneLetterDiff;
        string beenThere = adjWord;
        for(unsigned int i = 0; i < adjWord.size(); i++) {
            char letterStorage = adjWord[i];
            for (char j = 97; j < 122; j++) {
                adjWord[i] = j;
                if ((dict.find(adjWord)) && (adjWord != beenThere)) {
                    oneLetterDiff.push_back(adjWord);
                }
            }
            adjWord[i] = letterStorage;
        }
        neighbors.insert(make_pair(adjWord, oneLetterDiff));
    }
}


string WordLadder::breadth_first(Node &src, Node &dest) {
    int num = 999999;

    for (Node &a : neighbors) {
        distance[a] == num;
    }

    distance[src] = 0;
    queue<Node> to_visit;
    to_visit.push(src);
    string previous;

    while(!to_visit.empty()) {
        Node x = to_visit.front();
        previous = x;
        to_visit.pop();
        if(x == dest) {
            return true;
        }
        for (Node i : neighbors[x]) {
            if (distance[i] == num) {
                distance[i] = distance[x] + 1;
            }
            pred[i] = x;
            to_visit.push(i);
        }
    }
    return previous;
}


int WordLadder::findLongestLadder() {
    int num = 0;
    int longest = 0;
    vector<string> sol;
    vector<string> finalSol;
    vector<int> distanceStorage;

    distance.clear();
    pred.clear();
    sol.clear();
    finalSol.clear();

    for (auto &word : wordVec) {
        string bfs = breadth_first(word);
        num = distance[bfs];
        if (num > longest) {
            printLadderPath(word, bfs);
            finalSol = sol;
            longest = num;
        }
        distanceStorage.push_back(num);
        distance.clear();
        pred.clear();
        sol.clear();
    }
    for (auto &word : finalSol) {
        cout << word << endl;
    }
    return longest;
}


void WordLadder::printLadderPath(Node &src, Node& dest) {
    int var = 0;
    if (dest == NULL) {return;}

    if (src != dest) {
        finalSol.push_back(pred[dest]);
        printLadderPath(src, pred[dest]);
        var++;
    }
    cout << var << endl;;
}


int main () {
    readStartandEnd();
    isAdjacent(&dict);
    breadth_first(&start, &end);





    return 0;
}
