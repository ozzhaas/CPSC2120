// This is a sketch you can use for your "bad1" .. "bad3" programs...

#include <iostream>
#include <cstdlib>
using namespace std;


struct Node {
    int key;

    //Number of nodes in this node's subtree
    int size;

    Node *left;
    Node *right;
    Node (int k) { key = k; size = 1; left = right = NULL; }
};


void print_inorder(Node *T) {
    //Base Case
    if (T == NULL) {return;}

    print_inorder(T->left);
    cout << T->key << endl;
    print_inorder(T->right);

}


Node *insert_keep_balanced(Node *T, int val, int rank) {
    if (T == NULL) {return new Node(val);}

    int sizeOfLeft = 0;

    if (T->left != NULL) {
        sizeOfLeft = T->left->size;
    }
    else {
        sizeOfLeft = 0;
    }

    if (sizeOfLeft >= rank) {
        T->left  = insert_keep_balanced(T->left, val, rank);
    }
    else {
        T->right = insert_keep_balanced(T->right, val, rank - sizeOfLeft - 1);
    }


    // // Make sure T's size is correct, since its subtrees may have changed
    T->size = 1;
    if (T->left != NULL) T->size += T->left->size;
    if (T->right != NULL) T->size += T->right->size;
    return T;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: bad1 <input size>\n";
        return 0;
    }

    int N = atoi(argv[1]);  // get first command-line argument
    if (N<1 || N>100000) {
        cout << "Invalid input size!\n";
        return 0;
    }

    // Generate and print bad input of size N for prog1
    // (currently just generates an input of N random numbers)
    Node* T = NULL;

    for (int i = 0; i < N-1; i++) {
        T = insert_keep_balanced(T, (N-i), 123456789 % (i + 1));
    }

    print_inorder(T);

    return 0;
}
