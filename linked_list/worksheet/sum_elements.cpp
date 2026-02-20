#include "linkedlist.h"
#include <iostream>

using namespace std;

int sum(Node *head) {
  if (head == nullptr) {
    return 0;
  }

  int sumElements = head->data + sum(head->next);

  return sumElements;
}

int main() {
  LinkedList list;

  for (int i = 1; i <= 4; ++i) {
    list.insert(i);
  }

  list.display();

  cout << sum(list.getHead()) << endl;

  return 0;
}
