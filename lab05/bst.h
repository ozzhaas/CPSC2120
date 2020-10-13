#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <tuple>

using namespace std;


struct Node {
    double key;

    //Number of nodes in this node's subtree
    int size;

    Node *left;
    Node *right;
    Node (double k) { key = k; size = 1; left = right = NULL; }
};

Node *insert(Node *T, double k);
void print_inorder(Node *T);
Node *find(Node *T, double k);
Node *predfind(Node *T, double k);
Node *join(Node *L, Node *R);
Node *remove(Node *T, double k);
pair<Node *, Node *> split(Node *T, double k);
Node *insert_keep_balanced(Node *T, double k);
int get_rank(Node *root, double x);
Node *insert_keep_balanced(Node *T, double k);




#endif
