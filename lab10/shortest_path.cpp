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

typedef string Node; //a node is equivalent to a word
Node start;
Node end;

vector<string> wordVec;
vector<Node> nodeList;
StringIntMap dict;

map<Node, int> distance;
map<Node, Node> pred;
map<Node, vector<Node>> neighbors;
map<pair<Node, Node>, int> edge_wt;

int MAX_LEN = 999999;

WordLadder::WordLadder() {}


void build_graph(void) {
    int numrows = wordVec.size();
    int numcols = wordVec[0].length();

    for (int i = 0; i < numrows; i++) {
        for (int j = 0; j < numcols; j++) {
            nodeList.push_back(make_pair(i, j));
        }
    }
    int di[] = {+1, -1, 0, 0};
    int dj[] = {0, 0, +1, -1};

    for (int i = 1; i < numrows - 1; i++) {
        for (int j = 1; j < numcols - 1; j++) {
            for (int k = 0; k < 4; k++) {
                Node x = make_pair(i, j);
                Node nbr = make_pair(i + di[k], j + dj[k]);
                neighbors[x].push_back(nbr);
            }
        }
    }

}


void readStartandEnd(Node &src, Node &dest) {
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


void adjacencyList(StringIntMap &dict) {
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


string breadth_first(Node &src, Node &dest) {
    int num = 999999;

    for (Node a : neighbors) {
        distance[a] == num;
    }

    distance[src] = 0;
    queue<Node> to_visit;
    to_visit.push(src);
    string previous;

    while(!to_visit.empty()) {
        Node x = to_visit.front();
        previous = distance[x];
        to_visit.pop();
        if(x == dest) {
            return true;
        }
        for (auto &i : neighbors[x]) {
            if (distance[i] == num) {
                pred[i] = x;
                to_visit.push(i);
                distance[i] = distance[x] + 1;
            }
        }
    }
    return previous;
}


int findLongestLadder() {
    int num = 0;
    int longest = 0;
    vector<string> sol;
    vector<string> finalSol;
    vector<int> distanceStorage;

    distance.clear();
    pred.clear();
    sol.clear();
    finalSol.clear();

    for (auto word : wordVec) {
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
    for (auto word : finalSol) {
        cout << word << endl;
    }
    return longest;
}


void printLadderPath(Node &src, Node& dest) {
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
    string mainWord;
    ifstream input;
    input.open("words5.txt");
    while (input >> mainWord) {
        wordVec.push_back(mainWord);
    }

    readStartandEnd();
    isAdjacent(&dict);
    breadth_first(&start, &end);





    return 0;
}
