/*Kellen Haas
  CPSC 2120
  lab10
  11/20/20
*/

#ifndef STRINGINTMAP_H
#define STRINGINTMAP_H

#include <string>
#include <assert.h>
using namespace std;

class StringIntMap {

 private:

  struct Node {
    string key;
    int val;
    Node *next;
    Node(string k, int v, Node *n) { key = k; val = v; next = n; }
  };

  Node **table;  // array of pointers to linked lists
  int size;      // size of table, as currently allocated
  int num_elems; // number of elements stored in the table
  Node **allocate_table(int size);  // private helper function

 public:
  StringIntMap();
  ~StringIntMap();
  int &operator[](string key);
  bool find(string key);
  void insert(string key, int val);
  void remove(string key);
  void print(void);
  int get_num_elems(void);
  string *get_keys(void);
};

#endif
