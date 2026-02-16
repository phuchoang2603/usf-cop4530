#include <iostream>
#include <string>
using namespace std;

struct Node {
  string url;
  Node *prev;
  Node *next;
  Node(const string &u) : url(u), prev(nullptr), next(nullptr) {}
};

class BrowserHistory {
private:
  Node *current;

public:
  BrowserHistory(const string &homepage) { current = new Node(homepage); }
  ~BrowserHistory() {
    // revert back to homepage
    while (current->prev) {
      current = current->prev;
    }

    // start deleting
    while (current) {
      Node *temp = current;
      current = current->next;
      delete temp;
    }
  }

  // Vist a new_page and add it to BrowserHistory
  void visit(const string &url) {
    Node *to_delete = current->next;
    current->next = nullptr;

    // delete forward
    while (to_delete) {
      Node *temp = to_delete;
      to_delete = to_delete->next;
      delete temp;
    }

    // add new page
    Node *new_page = new Node(url);
    current->next = new_page;
    new_page->prev = current;

    // update current to new_page
    current = new_page;
  }

  // Turn x steps back
  string back(int steps) {
    while (steps > 0 && current->prev) {
      current = current->prev;
      steps--;
    }
    return current->url;
  }

  // Go x steps forward
  string forward(int steps) {
    while (steps > 0 && current->next) {
      current = current->next;
      steps--;
    }

    return current->url;
  }

  // Print BrowserHistory
  void printHistory() {
    Node *cur = current;

    // go to homepage
    while (cur->prev) {
      cur = cur->prev;
    }

    cout << "History: ";

    // traverse all
    while (cur) {
      cout << cur->url;
      if (cur == current) {
        cout << "* ";
      } else {
        cout << " ";
      }
      cur = cur->next;
    }

    cout << endl;
  }
};

int main() {
  BrowserHistory history("google");

  history.visit("github");
  history.visit("stackoverflow");
  history.printHistory();

  history.back(2);
  history.printHistory();

  history.forward(1);
  history.printHistory();

  history.visit("reddit");
  history.printHistory();

  return 0;
}
