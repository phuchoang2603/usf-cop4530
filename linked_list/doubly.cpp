#include <iostream>
#include <ostream>
using namespace std;

struct Node {
  int data;
  Node *prev;
  Node *next;
};

class LinkedList {
private:
  Node *head;
  Node *tail;

  // Search for a value and return the node ptr
  Node *search(int value) {
    Node *cur;
    for (cur = head; cur != nullptr; cur = cur->next) {
      if (cur->data == value) {
        return cur;
      }
    }
    return nullptr;
  }

public:
  LinkedList() {
    head = nullptr;
    tail = nullptr;
  }

  ~LinkedList() {
    Node *cur = head;
    Node *temp;

    while (cur != nullptr) {
      temp = cur;
      cur = cur->next;
      delete temp;
    }
  }

  // Insert new node at tail
  void insert(int value) {
    // allocate new node
    Node *newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (head == nullptr) {
      head = tail = newNode;
    } else {
      // establish bidirectional links
      tail->next = newNode;
      newNode->prev = tail;

      // update tail
      tail = newNode;
    }
  }

  // Remove a node given a value
  void remove(int value) {
    Node *cur = search(value);

    if (cur == nullptr) {
      cout << "no node contain " << value << endl;
      return;
    }

    if (cur == head) {
      head = cur->next;
      // check if list contain only one node
      if (head == nullptr) {
        tail = nullptr;
      } else {
        head->prev = nullptr;
      }
    } else if (cur == tail) {
      tail = cur->prev;
      tail->next = nullptr;
    } else {
      cur->prev->next = cur->next;
      cur->next->prev = cur->prev;
    }

    delete cur;
    display();
    return;
  }

  // Display list
  void display() {
    Node *cur;
    for (cur = head; cur != nullptr; cur = cur->next) {
      cout << cur->data << " ";
    }
    cout << endl;
  }
};

int main() {
  LinkedList *dl = new LinkedList;

  dl->insert(1);
  dl->insert(2);
  dl->insert(3);
  dl->insert(4);
  dl->display();

  dl->remove(5);
  dl->remove(3);
  dl->remove(1);
  dl->remove(4);
  dl->remove(2);

  delete dl;

  dl = new LinkedList;
  dl->insert(5);
  dl->display();
  delete dl;

  return 0;
}
