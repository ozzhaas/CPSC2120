/*Kellen Haas
  CPSC 2120
  Lab10
  11/20/20
*/

#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include "stringIntMap.h"


class WordLadder {

    private:
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

    public:
        WordLadder();
        ~WordLadder();
        pair<Node, Node> readStartandEnd());
        void adjacencyList(StringIntMap&);
        string breadth_first(Node src, Node dest);
        int findLongestLadder();
        void printLadderPath();












}



























#endif
