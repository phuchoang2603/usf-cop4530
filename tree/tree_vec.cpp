#include <iostream>
#include <vector>

using namespace std;

template <typename E> class Tree {
private:
  struct Node {
    E data;
    Node *parent;
    vector<Node *> children;
    Node(E value) : data(value), parent(nullptr) {}
  };
  Node *rootNode;

public:
  class Position {
  private:
    Node *node;
    friend class Tree<E>;

  public:
    Position(Node *n = nullptr) { node = n; }
    E &operator*() { return node->data; }

    bool isRoot() { return node->parent == nullptr; }
    bool isExternal() { return node->children.size() == 0; }

    Position parent() { return Position(node->parent); }
    vector<Position> children() {
      vector<Position> res;
      for (Node *child : node->children) {
        res.push_back(Position(child));
      }
      return res;
    }
  };

  Tree() { rootNode = nullptr; }
  Position root() { return rootNode; }

  Position addRoot(E value) {
    rootNode = new Node(value);
    return Position(rootNode);
  }

  Position addChild(Position p, E value) {
    Node *parent = p.node;
    Node *child = new Node(value);

    child->parent = parent;
    parent->children.push_back(child);

    return Position(child);
  }

  int depth(Position p) {
    if (p.isRoot()) {
      return 0;
    }
    return 1 + depth(Position(p.parent()));
  }

  int height(Position p) {
    if (p.isExternal()) {
      return 0;
    }
    int h = 0;
    for (Position child : p.children()) {
      h = max(h, height(child));
    }
    return 1 + h;
  }

  void preorder(Position p) {
    cout << *p << " ";
    for (Position child : p.children()) {
      preorder(child);
    }
  }

  void postorder(Position p) {
    for (Position child : p.children()) {
      postorder(child);
    }
    cout << *p << " ";
  }
};

int main() {
  Tree<string> T;
  auto A = T.addRoot("A");
  auto B = T.addChild(A, "B");
  auto C = T.addChild(A, "C");

  auto D = T.addChild(B, "D");
  auto E = T.addChild(C, "E");

  cout << "Preorder: ";
  T.preorder(A);
  cout << "\nPostorder: ";
  T.postorder(A);

  cout << "\nDepth of E: " << T.depth(E) << endl;
  cout << "Height of D: " << T.height(D) << endl;

  return 0;
}
