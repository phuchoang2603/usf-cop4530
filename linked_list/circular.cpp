#include <iostream>

using namespace std;

template <typename T> class CircularLinkedList {
  struct Node {
    T value;
    Node *next;
    Node(T val) : value(val), next(nullptr) {}
  };

  Node *head;

public:
  CircularLinkedList() : head(nullptr) {}

  void insert(T value, int cyclePos = -1) {
    Node *newNode = new Node(value);

    if (head == nullptr) {
      head = newNode;
    } else {
      Node *cur = head;
      while (cur->next != nullptr) {
        cur = cur->next;
      }
      cur->next = newNode;
    }

    // If cyclePos is specified, create a cycle to that position
    if (cyclePos >= 0) {
      // Traverse to cyclePos
      Node *cycleTarget = head;
      for (int i = 0; i < cyclePos && cycleTarget != nullptr;
           i++, cycleTarget = cycleTarget->next)
        ;

      // Traverse to last node
      Node *last = head;
      while (last->next != nullptr) {
        last = last->next;
      }

      // Create cycle from last to cyclePos
      last->next = cycleTarget;
    }
  }

  Node *detectCycle() {
    // If list have none or one node
    if (head == nullptr || head->next == nullptr)
      return nullptr;

    Node *slow = head;
    Node *fast = head;
    bool hasCycle = false;

    // Phase 1: Detect if list have Cycle
    // - fast: move two steps
    // - slow: move one step
    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) {
        hasCycle = true;
        break;
      }
    }
    if (!hasCycle) {
      return nullptr;
    }

    // Phase 2: Find cycleStart
    slow = head;
    while (slow != fast) {
      slow = slow->next;
      fast = fast->next;
    }

    return slow;
  }

  int findCycleLength(Node *cycleStart) {
    if (!cycleStart)
      return 0;

    int length = 0;
    Node *cur = cycleStart;

    do {
      cur = cur->next;
      length++;
    } while (cur != cycleStart);

    return length;
  }

  void printList() {
    if (!head) {
      return;
    }

    Node *cycleStart = detectCycle();
    int encountered = 0;
    Node *cur = head;

    while (cur != nullptr) {
      cout << cur->value << " -> ";

      if (cur == cycleStart) {
        encountered++;
        if (encountered == 2) {
          break;
        }
      }

      cur = cur->next;
    }

    cout << endl;
  }

  ~CircularLinkedList() {
    if (!head)
      return;

    // Break cycle if exists
    Node *cycleStart = detectCycle();
    if (cycleStart) {
      Node *cur = head;
      while (cur->next != cycleStart) {
        cur = cur->next;
      }
      cur->next = nullptr;
    }

    // Delete all nodes
    while (head != nullptr) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
  }
};

int main() {
  CircularLinkedList<int> *list = new CircularLinkedList<int>;

  list->insert(1);
  list->insert(2);
  list->insert(3);
  list->insert(4);
  list->insert(5);
  list->insert(6);
  list->insert(7);
  list->insert(8, 8);

  list->printList();

  // Detect cycle and find its length
  auto cycleStart = list->detectCycle();
  if (cycleStart) {
    cout << "Cycle detected at node with value: " << cycleStart->value << endl;
    cout << "Cycle length: " << list->findCycleLength(cycleStart) << endl;
  } else {
    cout << "No cycle detected." << endl;
  }

  delete list;

  return 0;
}
