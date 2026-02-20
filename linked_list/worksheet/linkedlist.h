#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

struct Node {
  int data;
  Node *next;
  explicit Node(int value = 0) : data(value), next(nullptr) {}
};

class LinkedList {
public:
  LinkedList();
  ~LinkedList();

  void insert(int value);
  Node *findMiddle() const;
  void display() const;
  Node *getHead() const;
  void setHead(Node *newHead);

private:
  Node *head_;
};

inline LinkedList::LinkedList() : head_(nullptr) {}

inline LinkedList::~LinkedList() {
  Node *cur = head_;
  while (cur != nullptr) {
    Node *temp = cur;
    cur = cur->next;
    delete temp;
  }
}

inline void LinkedList::insert(int value) {
  Node *newNode = new Node(value);
  if (head_ == nullptr) {
    head_ = newNode;
  } else {
    Node *tail = head_;
    while (tail->next != nullptr) {
      tail = tail->next;
    }
    tail->next = newNode;
  }
}

inline Node *LinkedList::findMiddle() const {
  Node *slow = head_;
  Node *fast = head_;
  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}

inline void LinkedList::display() const {
  Node *cur = head_;
  while (cur != nullptr) {
    std::cout << cur->data << " ";
    cur = cur->next;
  }
  std::cout << std::endl;
}

inline Node *LinkedList::getHead() const { return head_; }

inline void LinkedList::setHead(Node *newHead) { head_ = newHead; }

#endif // LINKEDLIST_H
