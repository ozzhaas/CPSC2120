/* Order by frequency
   1. read in input
   2. store all comma separated ints in a hash table
   3. sort the vector based on the frequency count of each number
      (highest frequency -> lowest frequency)
   4.
*/






#include <iostream>
#include <fstream>
using namespace std;

struct Node {
  string myInts;
  Node *next;
  Node (string m, Node *n) { myInts = m; next = n; }
};

const int size = 1000000;

int myhash(string m, int table_size)
{
  unsigned int i, h = 0;
  for (i=0; i<m.length(); i++)
    h = (h * 2917 + (unsigned int)m[i]) % table_size;
  return h;
}

int count_occurrences(Node *head, string m)
{
  int count = 0;
  for (Node *n = head; n != NULL; n = n->next)
    if (n->name == m) count++;
  return count;
}

int main(void)
{
  Node **head;
  head = new Node *[size];
  for (int i=0; i<size; i++) head[i] = NULL;
  string in;
  while (cin >> in) {
    int h = myhash(in, size);
    if (count_occurrences(head[h], in) == 1) cout << in << "\n";
    head[h] = new Node (in, head[h]);
  }
  return 0;
}
