#include <iostream>
struct Node {
  int data;
  Node *next;
};

class LinkedList {
  Node *head;

public:
  // Constructor
  LinkedList() { head = nullptr; };

  // Destructor
  ~LinkedList() {
    Node *cur = head;

    while (cur != nullptr) {
      Node *temp = cur;
      cur = cur->next;
      delete temp;
    }
  }

  // Insert a new element at the end
  void insert(int value) {
    // allocate new node
    Node *newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    // update old last node point to new one
    if (head == nullptr) {
      head = newNode;
    } else {
      Node *p;
      for (p = head; p->next != nullptr; p = p->next)
        ;
      p->next = newNode;
    }
  }

  // Insert a new element at the front
  void insertFront(int value) {
    Node *newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
  }

  // Search an element
  void insertAfter(int valueToFind, int valueToInsert) {
    // lookup the node contains valueToFind
    Node *current;
    for (current = head; current->data != valueToFind; current = current->next)
      ;

    // check if it was found
    if (current != nullptr) {
      Node *newNode = new Node();
      newNode->data = valueToInsert;
      newNode->next = current->next;
      current->next = newNode;
    }
  }

  // Remove a element after a given value
  void remove(int valueToFind) {
    // lookup the node using two ptr
    Node *cur, *prev;
    for (cur = head, prev = nullptr; cur != nullptr && cur->data != valueToFind;
         prev = cur, cur = cur->next)
      ;

    // when head is the node contain valueToFind
    if (prev == nullptr) {
      head = head->next;
      delete cur;
    }

    prev->next = cur->next;
    delete cur;
  }

  // Display elements in the list
  void display() {
    Node *cur;
    for (cur = head; cur != nullptr; cur = cur->next) {
      std::cout << cur->data << " ";
    }
    std::cout << std::endl;
  }
};

int main() {
  LinkedList *l = new LinkedList;

  l->insert(10);
  l->insert(20);
  l->insert(30);
  l->display();

  l->insertAfter(20, 40);
  l->insertFront(0);
  l->display();

  l->remove(40);
  l->display();

  delete l;

  l = new LinkedList;
  l->insert(30);
  l->display();
  delete l;

  return 0;
}
