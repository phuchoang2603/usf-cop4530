#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *next;
  Node(int val) {
    data = val;
    next = nullptr;
  }
};

class Queue {
  Node *frontNode;
  Node *rear;
  int size;

public:
  Queue() {
    frontNode = nullptr;
    rear = nullptr;
    size = 0;
  };

  bool empty() { return frontNode == nullptr; }

  void enqueue(int value) {
    Node *newNode = new Node(value);

    if (empty()) {
      frontNode = rear = newNode;
    } else {
      rear->next = newNode;
      rear = newNode;
    }

    size++;
  }

  void dequeue() {
    if (empty()) {
      return;
    }

    Node *temp = frontNode;
    frontNode = frontNode->next;
    delete temp;
    size--;
  }

  int front() {
    if (empty()) {
      return -1;
    }

    return frontNode->data;
  }
};

int main() {
  Queue q;

  for (int i = 0; i < 10; i++) {
    q.enqueue(i);
  }

  while (!q.empty()) {
    cout << q.front() << " ";
    q.dequeue();
  }

  cout << endl;
}
