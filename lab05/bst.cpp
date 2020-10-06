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
using namespace std;

struct Node {
    int key;

    //Number of nodes in this node's subtree
    int size;

    Node *left;
    Node *right;
    Node (int k) { key = k; size = 1; left = right = NULL; }
};


/*Function: Insert key k into tree T, returning a pointer to the resulting tree*/
Node *insert(Node *T, int k) {
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


/*Function: Return a pointer to the node with key k in tree T,
  or NULL if it doesn't exist*/
Node *find(Node *T, int k) {
    //Base case
    if (T == NULL) {return NULL;}
    if (k == T->key) {return T;}
    if (k < T->key) {return find(T->left, k);}
    else {return find(T->right, k);}

}


/*Function: Return pointer to the node with key k if it exists
  If not, return a pointer to the node with the largest key smaller than k (i.e.,
  k's predecessor) or NULL if there isn't any node with key smaller than k.*/
Node *predfind(Node *T, int k) {
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
Node *remove(Node *T, int k) {
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
pair<Node *, Node *> split(Node *T, int k) {
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
Node *insert_keep_balanced(Node *T, int k)
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
        if (k < T->key) {T->left  = insert_keep_balanced(T->left,  k);}
        else {T->right = insert_keep_balanced(T->right, k);}
    }

    // Make sure T's size is correct, since its subtrees may have changed
    T->size = 1;
    if (T->left != NULL) T->size += T->left->size;
    if (T->right != NULL) T->size += T->right->size;
    return T;
}

int main(void)
    {
    /*Testing insert and print_inorder*/
    int A[10];

    /*Put 0..9 into A[0..9] in random order*/
    for (int i=0; i<10; i++) A[i] = i;
    for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);

    /*Insert contents of A into a BST*/
    Node *T = NULL;
    for (int i=0; i<10; i++) T = insert(T, A[i] * 10);


    /*Print contents of BST (should be 0, 10, 20, ..., 90 in sorted order)*/
    cout << "\nTesting insert and print_inorder (should be 0,10,20,...,90)\n";
    print_inorder(T);
    cout << "Size (should be 10): " << (T ? T-> size : 0) << "\n";

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~Test Find~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /*Elements 0,10,...,90 should be found; 100 should not be found*/
    cout << "\nTesting find (should be 0,10,20,...,90 found, 100 not found)\n";
    for (int i=0; i<=100; i+=10)
        if (find(T,i)) {cout << i << " found\n";}
        else {cout << i << " not found\n";}


    /* ~~~~~~~~~~~~~~~~~~~~~~~~~Test predfind~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /* -- if nothing printed, that's good news */
    if (predfind(T,-1)) {cout << "Error: predfind(-1) returned something and should have returned NULL\n";}
    if (predfind(T,50)->key != 50) {cout << "Error: predfind(50) didn't return the node with 50 as its key\n";}
    for (int i=0; i<=90; i+=10) {
        if (predfind(T,i+3)->key != i) {cout << "Error: predfind(" << i+3 << ") didn't return the node with " << i << " as its key\n";}
    }


    /* ~~~~~~~~~~~~~~~~~~~~~~~~~Test Split~~~~~~~~~~~~~~~~~~~~~~~~~ */
    cout << "\nTesting split\n";
    Node *L, *R;
    tie(L,R) = split(T, 20);
    /*Alternatively, could say:
      pair<Node *, Node *> result = split(T, 20);
      Node *L = result.first, *R = result.second;*/

    cout << "Contents of left tree after split (should be 0..20):\n";
    print_inorder(L);
    cout << "\nSize left subtree (should be 3): " << L->size << "\n";
    cout << "Contents of right tree after split (should be 30..90):\n";
    print_inorder(R);
    cout << "\nSize right subtree (should be 7): " << R->size << "\n";


    /* ~~~~~~~~~~~~~~~~~~~~~~~~~Test Join~~~~~~~~~~~~~~~~~~~~~~~~~ */
    T = join(L, R);
    cout << "\nTesting join\n";
    cout << "Contents of re-joined tree (should be 0,10,20,...,90)\n";
    print_inorder(T);
    cout << "\nSize (should be 10): " << T->size << "\n";

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~Test Remove~~~~~~~~~~~~~~~~~~~~~~~~~ */
    cout << "\nTesting remove\n";
    for (int i=0; i<10; i++) A[i] = i*10;
    for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
    for (int i=0; i<10; i++) {
      T = remove(T, A[i]);
      cout << "Contents of tree after removing " << A[i] << ":\n";
      print_inorder(T);
      cout << "\nSize of tree after this removal (should be 1 less than before): " << (T ? T->size : 0) << "\n";
    }


    /* ~~~~~~~~~~~~~~~~~~~~~Test insert_keep_balanced~~~~~~~~~~~~~~~~~~~~~ */
    /*test insert_keep_balanced basic functionality
      insert contents of A into a BST*/
    for (int i=0; i<10; i++) T = insert_keep_balanced(T, A[i]);


    /*Print contents of BST*/
    cout << "\n" << "Testing insert_keep_balanced (should be 0,10,20,..90)\n";
    print_inorder(T);
    cout << "\n" << "Size (should be 10): " << T->size << "\n";

    /*Test insert_keep_balanced speed*/
    cout << "Inserting 10 million elements in order; this should be very fast if insert_balance is working...\n";
    for (int i=0; i<10000000; i++) T = insert_keep_balanced(T, i+10); // 10 million ints starting at 10
    cout << "Done\n";
    cout << "Size (should be 10000010): " << T->size << "\n\n";

    return 0;
}
