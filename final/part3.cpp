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
  int freq = 0;
  Node *next;
  Node (string m, int f, Node *n) { myInts = m; freq = f; next = n; }
};

const int size = 1000000;

int myhash(string m, int table_size)
{
  unsigned int i, h = 0;
  for (i=0; i<m.length(); i++)
    h = (h * 2917 + (unsigned int)m[i]) % table_size;
  return h;
}

void count_occurrences(Node *head, string m)
{
  int count = 0;
  for (Node *n = head; n != NULL; n = n->next)
    if (n->myInts == m) {
        count++;
        n->freq = count;
    }
}

// Insert to keep list sorted
Node *insert_sorted(Node *head, int val)
{
  // Base case: inserting new first element
  if (head == NULL || val < head->freq) return new Node(freq, head);
  head->next = insert_sorted(head->next, val);
  return head;
}


void print_ints(Node *head) {
    if (head == NULL) return;
    print_ints(head->next);

    cout << head->myInts << "\n";
}

int main(void)
{
  Node *head;
  int max = 0;

  for (int i=0; i<size; i++) head[i] = NULL;
  string in;
    while (cin >> in) {
        head = insert_sorted(head, in);
        // int h = myhash(in, size);
        count_occurrences(head[h], in);
        print_ints(head);
    }


  return 0;
}
