#include "linkedlist.h"

int main() {
  LinkedList list;
  for (int i = 1; i <= 7; ++i) {
    list.insert(i);
  }

  list.display();
  if (Node *middle = list.findMiddle()) {
    std::cout << middle->data << std::endl;
  }

  return 0;
}
