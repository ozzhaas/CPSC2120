/*Kellen Haas
  CPSC 2121
  Lab 1
  8/30/20
*/


#ifndef INTSET_H /* Prevent multiple inclusion... */
#define INTSET_H



class Intset {

    private:
        //Create a ListNode structure
        struct ListNode {
            int num;
            ListNode *next;
            ListNode(int num1, ListNode *next1 = nullptr) {
                num = num1;
                next = next1;
            }
        };
        //Create the head of the list
        ListNode *head;

    public:
        Intset();
        ~Intset();
        bool find(int key);
        void insert(int key);
        void remove(int key);
        void print(void);
    };

#endif
