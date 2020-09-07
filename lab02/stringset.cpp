/* Kellen Haas
   CPSC 2121
   Lab02
   09/06/20
*/


#include <iostream>
#include <string.h>
#include <assert.h>
#include "stringset.h"

using namespace std;

/* Return a hash for the string s in the range 0..table_size-1 */
int myhash(string s, int table_size) {
    unsigned int i, h = 0;
    for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)s[i]) % table_size;
    return h;
}



Stringset::Stringset() {
    size = 4;
    table = new Node *[size];// allocate table, initialize head ptrs all to NULL
    for (int i=0; i<size; i++)
    table[i] = NULL;
    num_elems = 0;
}


Stringset::~Stringset() {
    for (int i=0; i<size; i++) {
        while (table[i] != NULL) {
            Node *temp = table[i];
            table[i] = table[i]->next;
            delete temp;
        }
    }
    delete[] table;
}


/* Return true if key is in the set */
bool Stringset::find(string key) {
    int h = myhash(key, size);
    Node *n = table[h];
    while (n != NULL) {
        if (n->key == key) return true;
        n = n->next;
    }
    return false;
}


/* Inserts a new key.  It is an error if key is already in the set. */
void Stringset::insert(string key) {
    assert (!find(key));
    num_elems++;

    if (num_elems == size) {
        /*Expand table -- allocate new table of twice the size,
          re-insert all keys into new table, and de-allocate old table.*/
        cout << "Size of Table Doubled...\n";

        size = size * 2;
        //Create new table doubled in size
        Node **newTable = new Node*[size];

        //Initialize new table values to NULL
        for (int j=0; j<size; j++)
        newTable[j] = NULL;

        for (int i = 0; i < size/2; i++) {
            Node *n = table[i];
            //For every value in the old table that isn't null,
            //insert it into the new table, then remove the old
            //table's node
            while (n != NULL) {
                int h = myhash(n->key, size);
                newTable[h] = new Node(n->key, newTable[h]);
                Node *remNode = n;
                n = n->next;
                delete remNode;
            }
        }
    //Deallocate old table
    delete[] table;
    table = newTable;
    }
    //Insert new element
    int h = myhash(key, size);
    table[h] = new Node(key, table[h]);
}

/* Removes a key.  It is an error if key isn't in the set */
void Stringset::remove(string key) {
    assert (find(key));
    num_elems--;

    //Delete an element in the table
    int h = myhash(key, size);

    //If the element has a matching key remove it
    if (table[h]->key == key) {
        Node *remNode = table[h];
        table[h] = table[h]->next;
        delete remNode;
    }
    //Else iterator through the elements until you find the one
    //with a matching key, then remove it.
    else {
        Node *n = table[h];
        while (n->next->key != key) {
            n = n->next;
        }
        Node *remNode = n->next;
        n->next = remNode->next;
        delete remNode;
    }
}

/*Print the entire table as long as the element is not NULL*/
void Stringset::print(void) {
    //Print contents of table
    for (int i = 0; i < size; i++) {
        Node *n = table[i];
        while (n != NULL) {
            cout << n->key << " ";
            n = n->next;
            cout << "\n";
        }
    }
}
