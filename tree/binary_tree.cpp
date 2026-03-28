#include <iostream>

using namespace std;

template <typename E> class BinaryTree {
private:
  struct Node {
    E data;
    Node *left;
    Node *right;
    Node(E value) {
      data = value;
      left = nullptr;
      right = nullptr;
    }
  };

  Node *rootNode;
  int n;

public:
  class Position {
  private:
    Node *node;
    friend BinaryTree<E>;

  public:
    Position(Node *n = nullptr) { node = n; }
    E operator*() { return node->data; }

    bool isExternal() {
      return node->left == nullptr && node->right == nullptr;
    }
    bool isInternal() {
      return node->left != nullptr || node->right != nullptr;
    }
    bool isNull() { return node == nullptr; }

    Position left() { return Position(node->left); }
    Position right() { return Position(node->right); }
  };

  BinaryTree(E value) {
    rootNode = new Node(value);
    n = 1;
  };
  int size() { return n; }
  Position root() { return Position(rootNode); }

  // in order traversal
  void inorder(Position p) {
    if (p.isNull()) {
      return;
    }
    inorder(p.left());
    cout << *p << " ";
    inorder(p.right());
  }

  // insert a node to tree
  void insert(Position p, E value) {
    if (rootNode == nullptr) {
      rootNode = new Node(value);
      return;
    }

    if (value == *p) {
      return;
    }

    if (value < *p) {
      if (p.left().isNull()) {
        p.node->left = new Node(value);
        n++;
      } else {
        insert(p.left(), value);
      }
    } else {
      if (p.right().isNull()) {
        p.node->right = new Node(value);
        n++;
      } else {
        insert(p.right(), value);
      }
    }
  }

  // find minimum nodes
  Position findMin(Position p) {
    while (!p.isNull() && !p.left().isNull()) {
      p = p.left();
    }
    return p;
  }

  // delete nodes from the tree
  Position remove(Position p, E value) {
    if (p.isNull()) {
      return p;
    }

    if (value < *p) {
      p.node->left = remove(p.left(), value).node;
    } else if (value > *p) {
      p.node->right = remove(p.right(), value).node;
    } else {
      if (p.left().isNull()) {
        Node *temp = p.node->right;
        delete p.node;
        n--;
        return Position(temp);
      }

      if (p.right().isNull()) {
        Node *temp = p.node->left;
        delete p.node;
        n--;
        return Position(temp);
      }

      Position successor = findMin(p.right());
      p.node->data = *successor;
      p.node->right = remove(p.right(), *successor).node;
    }

    return p;
  }

  // binary search helper
  Position finder(E value, Position p) {
    if (p.isNull()) {
      return p;
    }

    if (value < *p) {
      return finder(value, p.left());
    } else if (value > *p) {
      return finder(value, p.right());
    } else {
      return p;
    }
  }

  // binary search
  Position find(E value) { return finder(value, root()); }
};
