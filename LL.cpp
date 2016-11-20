#include <iostream>
using namespace std;

struct Node {
    Node* next;
    int data;

    Node() {
        next = nullptr;
        data = 0;
    }

    Node(int data) {
        this->data = data;
    }

    ~Node() {
        delete next;
    }

    void printList(Node* node) {
        if (node == NULL) return;
        cout << node->data << endl;
        printList(node->next);
    }
};

int main() {
    Node* root = new Node(5);
    root->next = new Node(6);
    root->next->next = new Node(7);
    root->next->next->next = new Node(2);
    root->printList(root);
    
}
