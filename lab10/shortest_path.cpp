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

vector<string> words;
vector<Node> all_nodes;
StringIntMap dict;

map<Node, int> distance;
map<Node, Node> pred;
map<Node, vector<Node>> neighbors;



// void build_graph(void) {
//     int numrows = words.size();
//     int numcols = words[0].length();
//
//     for (int i = 0; i < numrows; i++) {
//         for (int j = 0; j < numcols; j++) {
//             all_nodes.push_back(make_pair(i, j));
//         }
//     }
//     int di[] = {+1, -1, 0, 0};
//     int dj[] = {0, 0, +1, -1};
//
//     for (int i = 1; i < numrows - 1; i++) {
//         for (int j = 1; j < numcols - 1; j++) {
//             for (int k = 0; k < 4; k++) {
//                 Node x = make_pair(i, j);
//                 Node nbr = make_pair(i + di[k], j + dj[k]);
//                 neighbors[x].push_back(nbr);
//             }
//         }
//     }
//
// }


void readStartandEnd(void) {
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
    start = s;
    end = d;
}


bool isOneLetterDiff(void) {
    if (start.length() != end.length()) {return false;}
    int diff = 0;
    for (int i = 0; i < start.lenght(); i++) {
        if (start[i] != end[i]) {
            diff += 1;
        }
        if (diff > 1) {
            return false;
        }
    }
    if (diff == 1) {return true;}
    else {return false;}
}

//
// void adjacencyList(StringIntMap &dict) {
//     int length = 0;
//
//
// }


// string breadth_first(Node &src, Node &dest) {
//     int num = 999999;
//
//     for (Node a : neighbors) {
//         distance[a] == wordVec;
//     }
//
//     distance[src] = 0;
//     queue<Node> to_visit;
//     to_visit.push(src);
//     string previous;
//
//     while(!to_visit.empty()) {
//         Node x = to_visit.front();
//         previous = distance[x];
//         to_visit.pop();
//         if(x == dest) {
//             return true;
//         }
//         for (auto &i : neighbors[x]) {
//             if (distance[i] == num) {
//                 pred[i] = x;
//                 to_visit.push(i);
//                 distance[i] = distance[x] + 1;
//             }
//         }
//     }
//     return previous;
// }


int findLongestLadder(StringIntMap dict) {
    if (dict.find(start) || dict.find(end)) {return 0;}
    queue<Node> to_visit;
    to_visit.push_back(start);
    dict.remove(start);
    while (!to_visit.empty()) {
        string curr = to_visit.front();
        to_visit.pop();
        for (auto i : dict) {
            if (isOneLetterDiff(curr.first, dict[i])) {
                if (dict[i] == end) {
                    return curr.second + 1;
                }
                to_visit.push(dict[i], cur.second + 1);
                dict.remove(i);
            }
        }
    }
    return 0;
}


void printLadderPath() {
    int var = 0;
    if (end == NULL) {return;}

    if (start != end) {
        finalSol.push_back(pred[end]);
        printLadderPath(start, pred[end]);
        var = findLongestLadder();
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

    StringIntMap mainDict;
    readStartandEnd();
    findLongestLadder(mainDict);
    printLadderPath();
    // isAdjacent(&dict);
    // breadth_first(&start, &end);





    return 0;
}
