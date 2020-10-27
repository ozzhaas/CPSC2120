
/* Kellen Haas
  CPSC 2120
  Lab4
  9/26/20
*/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <tuple>
#include <string>
using namespace std;

struct Node {
    string key;

    //Number of nodes in this node's subtree
    int size;

    Node *left;
    Node *right;
    Node *parent;
    Node (string k) { key = k; size = 1; parent = left = right = NULL; }
};


/*Function: Insert key k into tree T, returning a pointer to the resulting tree*/
Node *insert(Node *T, string k) {
    //Base case
    if (T == NULL) return new Node(k);

    //Left side of tree for values less than k
    if (k < T->key) {
        T->left = insert(T->left, k);
    }
    //Right side of tree for values greater than or equal to k
    else {
        T->right = insert(T->right, k);
    }
    T->size++;
    return T;
}


/*Function: Prints out the inorder traversal of T
  (i.e., the contents of T in sorted order)*/
void print_inorder(Node *T) {
    //Base Case
    if (T == NULL) {return;}

    print_inorder(T->left);
    cout << T->key << endl;
    print_inorder(T->right);

}

int bstHeight(Node* T) {
    int lHeight = 0;
    int rHeight = 0;

    if (T == NULL) {
        return -1;
    }
    lHeight = bstHeight(T->left);
    rHeight = bstHeight(T->right);

    if (lHeight > rHeight) {
        return lHeight + 1;
    }
    else {
        return rHeight + 1;
    }

}




void printLevel(Node* root, int lev) {
    if (root == NULL) {
        return;
    }
    else if(lev == 1) {
        cout << root->key << " ";
    }
    else {
        printLevel(root->left, lev - 1);
        printLevel(root->right, lev - 1);
    }
}


void printLevXLev(Node* root) {
    if (root == NULL) {
        return;
    }
    int height = bstHeight(root);
    for (int i = 1; i <= height; i++) {
        cout << "\n" <<"Level " << i << ":" << endl;
        printLevel(root, i);
        cout << endl;
        if (root == NULL){break;}
    }
}


/*Function: Return a pointer to the node with key k in tree T,
  or NULL if it doesn't exist*/
Node *find(Node *T, string k) {
    //Base case
    if (T == NULL) {return NULL;}
    if (k == T->key) {return T;}
    if (k < T->key) {return find(T->left, k);}
    else {return find(T->right, k);}

}


/*Function: Return pointer to the node with key k if it exists
  If not, return a pointer to the node with the largest key smaller than k (i.e.,
  k's predecessor) or NULL if there isn't any node with key smaller than k.*/
Node *predfind(Node *T, string k) {
    if (T == NULL) {return NULL;}
    if (k == T->key) {return T;}
    if (k <= T->key) {return predfind(T->left, k);}
    if (k > T->key) {
        if (predfind(T->right, k) == NULL) {
            return T;
        }
        else {
            return predfind(T->right, k);
        }
    }
    return T;
}

/*Function: Join trees L and R (with L containing keys all <= the keys in R)
  Return a pointer to the joined tree.*/
Node *join(Node *L, Node *R)
{

    if (L == NULL) {return R;}
    if (R == NULL) {return L;}
    int total = L->size + R->size;

    //Pick random number in {0, 1, ..., total-1}
    int randn = rand() % total;

    //If the probability is (L->size / total)
    if (randn < L->size) {
    //Make L the root of the joined tree in this case
        L->right = join(L->right, R);
        if (L->left) {L->size += L->left->size;}
        if (L->right) {L->size += L->right->size;}
        return L;
    }
    //If the probability is (R->size / total)
    else {
        //Make R the root of the joined tree in this case
        R->left = join(L, R->left);
        if (R->left) {R->size += R->left->size;}
        if (R->right) {R->size += R->right->size;}
        return R;
    }
}


/*Function: Remove key k from T, returning a pointer to the resulting tree.
  if k isn't present in T, then return the pointer to T's root, with T unchanged*/
Node *remove(Node *T, string k) {
    //Base Case
    if (T == NULL) {return NULL;}

    //Delete the root
    if (k == T->key) {return join(T->left, T->right);}

    //Left side of tree
    if (k < T->key) {T->left = remove(T->left, k);}
    //Right side of tree
    else {T->right = remove(T->right, k);}
    T->size--;
    return T;
}


/*Function: Split tree T on key k into tree L (containing keys <= k)
  and a tree R (containing keys > k)*/
pair<Node *, Node *> split(Node *T, string k) {
    pair <Node*, Node*> result;
    //Base case
    if (T == NULL) {return (make_pair((Node*)NULL, (Node*)NULL));}

    if (k < T->key) {
        pair <Node*, Node*> result = split(T->left, k);
        T->left = result.second;
        result.second = NULL;
        if (result.first != NULL) {
            T->size = T->size - (result.first)->size;
        }
        return make_pair(result.first, T);
    }
    if (k >= T->key) {
        pair <Node*, Node*> result = split(T->right, k);
        T->right = result.first;
        result.first = NULL;
        if (result.second != NULL) {
            T->size = T->size - (result.second)->size;
        }
        return make_pair(T, result.second);
    }
    return result;
}


/*Function: Insert key k into the tree T, returning a pointer to
the resulting tree keep the tree balanced by using randomized balancing:
    if N represents the size of our tree after the insert, then
        - with probability 1/N, insert k at the root of T (by splitting on k)
        - otherwise, recursively call insert_keep_balanced on the left or right*/
Node *insert_keep_balanced(Node *T, string k)
{
    if (T == NULL) {return new Node(k);}

    if (rand() % (1 + T->size) == 0) {
        //With probability 1/N, insert at root...
        pair<Node *, Node *> result = split (T, k);

        /*We can re-use T for new root, since result keeps pointers to
        remnants of original tree after splitting it*/
        T = new Node(k);
        T->left = result.first;
        T->right = result.second;
    }
    // Otherwise, recurseively insert on left or right side...
    else {
        if (k < T->key) {
            Node* LChild = insert_keep_balanced(T->left,  k);
            T->left = LChild;
            LChild->parent = T;

        }
        else {
            Node* RChild = insert_keep_balanced(T->right, k);
            T->right = RChild;
            RChild->parent = T;
        }
    }

    // Make sure T's size is correct, since its subtrees may have changed
    T->size = 1;
    if (T->left != NULL) T->size += T->left->size;
    if (T->right != NULL) T->size += T->right->size;
    return T;
}

int main(void) {
    ifstream input;
    input.open("prob2_input.txt");
    string in1, in2;

    Node* M = NULL;
    while (input >> in1 >> in2) {
        M = insert_keep_balanced(M, in1);
    }

    printLevXLev(M);


    return 0;
}
