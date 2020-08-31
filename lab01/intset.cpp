/*Kellen Haas
  CPSC 2121
  Lab 1
  8/30/20
*/


#include <iostream>
#include <assert.h>
#include "intset.h"

using namespace std;

//Constructor to create the Intset object
Intset::Intset() {
    //Initialize the head to null
    head = nullptr;
}

//Destructor to remove the Intset Object and the list entirely
Intset::~Intset() {
    //Make a pointer to the head
    ListNode *headPtr = head;

    //Loop until the end of the list...
    while (headPtr != nullptr) {

        /*Make a ListNode pointer object
          to store the garbage nodes*/
        ListNode *junkNode = headPtr;

        //Move the head to the next node
        headPtr = headPtr->next;

        //Delete the garbage node
        delete junkNode;
    }
}

/* Return true if key is in the set */
bool Intset::find(int key) {
    //Create a temp ListNode pointer and assign it the head's value
    ListNode *tmp = head;

    /* Linear search for key...
       if the head is null or the head's value
       is the same as the key return false*/
    if (head == nullptr || head->num > key) {
        return false;
    }

    //While the tmp is not null keep looping
    while (tmp != nullptr) {
        //If tmp's value is equal to key return true
        if (tmp->num == key) {
            return true;
        }
        //Else move onto the next node
        else {
            tmp = tmp->next;
        }
    }
    return false;
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Intset::insert(int key) {
    //Create a ListNode pointer to the head and the previous node
    ListNode *headPtr;
    ListNode *prevNodePtr;

    assert (!find(key));

    /*If the head is null or head's value is greater than
      or equal to the key create the new node to insert at
      the front of the list*/
    if (head == nullptr || head->num >= key) {
        head = new ListNode(key, head);
    }
    /*Else point the previous node pointer to the head
      and move the headPtr to the next node */
    else {
        prevNodePtr = head;
        headPtr = head->next;

        /*While the headPtr isn't null and head's value is less
          than the key, reassign the previous node pointer to
          the headPtr and move the headPtr to the next node*/
        while (headPtr != nullptr && headPtr->num < key) {
            prevNodePtr = headPtr;
            headPtr = headPtr->next;
        }
        /*Create a new node after the previous node with key
          and headPtr passed into the constructor*/
        prevNodePtr->next = new ListNode(key, headPtr);
    }
}

/* Removes a key.  It is an error if key isn't in the set */
void Intset::remove(int key) {
    assert (find(key));

    //Create a ListNode pointer to the head and the previous node
    ListNode *prevNodePtr, *headPtr;

    //If the head is null then return
    if (!head) {return;}

    /*If the head's value is equal to the key
      assign headPtr to the head and then move
      the head to the next node and then delete
      the headPtr*/
    if (head->num == key) {
        headPtr = head;
        head = head->next;
        delete headPtr;
    }

    /*Else assign headPtr to head and then start loop to assign
      the previous node pointer to headPtr and move the headPtr
      on to the next node*/
    else {
        headPtr = head;

        while(headPtr != nullptr && headPtr->num != key) {
            prevNodePtr = headPtr;
            headPtr = headPtr->next;
        }

        /*If the headPtr isn't null assign the node after
          previous node to the node after headPtr, then
          delete headPtr*/
        if (headPtr) {
            prevNodePtr->next = headPtr->next;
            delete headPtr;
        }
    }
}

/*Function to display the entire list by creating a pointer
  to the head and incrementing it through the list*/
void Intset::print(void) {
    ListNode *headPtr = head;
    while (headPtr) {
        cout << headPtr->num << " ";
        headPtr = headPtr->next;
    }
    cout << "\n";
}
