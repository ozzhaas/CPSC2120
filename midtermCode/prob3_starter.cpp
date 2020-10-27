#include <iostream>
#include <algorithm>
using namespace std;


struct Node {
  int val;
  Node *next;
  Node (int v, Node *n) { val = v; next = n; }
};

Node **T; // array of Node *s for hash table
int table_size = 1000000;

// check out this awesome hash function!
// Guaranteed to output a hash value in the range 0 ... 999,999
unsigned int myhash(int x)
{
  return ((unsigned)x * 123147 + 293871) % 100 + 900000;
}

bool find(int x)
{
  for (Node *n = T[myhash(x)]; n != NULL; n = n->next)
    if (n->val == x) return true;
  return false;
}

bool occupied(int x) {
    Node* n = T[myhash(x)];
    if (n != NULL) {
        return true;
    }
    else {
        return false;
    }
    return false;
}


int insert(int x)
{
    int probe = 0;
    int index = myhash(x);
    while (occupied(index)) {
        index += 1;
        probe++;
    }
    T[index] = new Node(x, T[index]);
    return probe;
}

int main(void)
{
  int N; // size of input
  if (!(cin >> N) || N < 1 || N > 100000) {
    cout << "Invalid input size!\n";
    return 0;
  }

  // read input
  int *A = new int[N];
  for (int i=0; i<N; i++)
    if (!(cin >> A[i]) || A[i]<0) {
      cout << "Invalid input!\n";
      return 0;
    }

  // initialize hash table -- if I make it have size 10,000, then the
  // average length of a linked list should be small...
  T = new Node *[table_size];
  for (int i=0; i<table_size; i++)
    T[i] = NULL;

  int p = 0;
  int count = 0;
  for (int i=0; i<N; i++)
    if (!find(A[i])) {
      count++;
      p = insert(A[i]);
    }



  cout << "Locations Probed: " << p << endl;
  return 0;
}
