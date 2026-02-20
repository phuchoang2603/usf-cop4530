#include "linkedlist.h"

Node *reverse(Node *head) {
  if (head == nullptr || head->next == nullptr) {
    return head;
  }

  Node *new_head = reverse(head->next);
  head->next->next = head;
  head->next = nullptr;

  return new_head;
}

int main() {
  LinkedList list;

  for (int i = 1; i <= 7; ++i) {
    list.insert(i);
  }

  list.display();

  list.setHead(reverse(list.getHead()));
  list.display();

  return 0;
}
