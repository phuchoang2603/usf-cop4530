#include <cstddef>
#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *next;
};

class LinkedQueue {
  Node *front;
  Node *rear;

public:
  LinkedQueue() {
    front = nullptr;
    rear = nullptr;
  };

  void enqueue(int value) {
    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    rear->next = newNode;
  }
};
