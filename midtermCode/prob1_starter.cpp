#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *next;
    Node (int k, Node *n) { key = k; next = n; }
};

void print_list(Node *head) {
    for (Node *n = head; n != NULL; n = n->next) cout << n->key << " ";
    cout << "\n";
}

int size(Node* head) {
    int count = 0;
    Node* tmp = head;

    while (tmp != NULL) {
        count++;
        tmp = tmp->next;
    }
    return count;
}



// Restore list to sorted order.  Return the head pointer of the resulting list.
Node *fix_list(Node *head) {
    int arr[size(head)];
    int i = 0;
    Node* currNode = head;

    while(currNode != NULL) {
        arr[i++] = currNode->key;
        currNode = currNode->next;
    }



    for (int j = 0; j < size(head); j++) {
        if (arr[j] > arr[j+1]) {
            swap(arr[j], arr[j+1]);
        }
    }

    Node* newHead = NULL;
    for (int i = size(head)-1; i >= 0; i--) {
        newHead = new Node(arr[i], newHead);
    }

    return newHead;
}


int main(void) {
    Node *head = NULL;

    // Make list with one out-of-place node
    for (int x=100; x>=50; x-=9) head = new Node(x, head);
    head = new Node(87, head);
    for (int x=45; x>=0; x-=13) head = new Node(x, head);

    cout << "Original list:  "; print_list(head);
    cout << "Array: " << endl;
    cout << "Corrected list: "; print_list(fix_list(head));
}
