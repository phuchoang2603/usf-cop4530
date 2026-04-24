#ifndef LINKED_TREE_H
#define LINKED_TREE_H

#include <vector>

using namespace std;

template <typename E> class LinkedTree {
private:
  struct Node {
    E data;
    Node *parent;
    Node *firstChild;
    Node *nextSibling;

    Node(E value)
        : data(value), parent(nullptr), firstChild(nullptr), nextSibling(nullptr) {}
  };

  Node *rootNode;
  int nodeCount;

  // Deletes all nodes recursively.
  void clearNode(Node *node) {
    if (node == nullptr) {
      return;
    }

    Node *child = node->firstChild;
    while (child != nullptr) {
      Node *nextChild = child->nextSibling;
      clearNode(child);
      child = nextChild;
    }

    delete node;
  }

  // Collects preorder positions recursively.
  void collectPreorder(Node *node, vector<Node *> &items) {
    if (node == nullptr) {
      return;
    }

    items.push_back(node);
    Node *child = node->firstChild;
    while (child != nullptr) {
      collectPreorder(child, items);
      child = child->nextSibling;
    }
  }

public:
  class Position {
  private:
    Node *node;
    friend class LinkedTree<E>;

  public:
    Position(Node *value = nullptr) : node(value) {}
    E &operator*() { return node->data; }
    bool isNull() { return node == nullptr; }
    bool isRoot() { return node != nullptr && node->parent == nullptr; }
    bool isExternal() { return node != nullptr && node->firstChild == nullptr; }
    bool isInternal() { return node != nullptr && node->firstChild != nullptr; }
    Position parent() { return Position(node == nullptr ? nullptr : node->parent); }
    Position firstChild() {
      return Position(node == nullptr ? nullptr : node->firstChild);
    }
    Position nextSibling() {
      return Position(node == nullptr ? nullptr : node->nextSibling);
    }
  };

  // Initializes an empty linked tree.
  LinkedTree() : rootNode(nullptr), nodeCount(0) {}

  // Releases all nodes.
  ~LinkedTree() { clear(); }

  // Clears tree content.
  void clear() {
    clearNode(rootNode);
    rootNode = nullptr;
    nodeCount = 0;
  }

  // Returns true if tree has no nodes.
  bool isEmpty() { return rootNode == nullptr; }

  // Returns number of nodes in tree.
  int size() { return nodeCount; }

  // Returns root position.
  Position root() { return Position(rootNode); }

  // Adds or replaces root node.
  Position addRoot(E value) {
    clear();
    rootNode = new Node(value);
    nodeCount = 1;
    return Position(rootNode);
  }

  // Adds child node at end of children list.
  Position addChild(Position parentPosition, E value) {
    if (parentPosition.isNull()) {
      return Position(nullptr);
    }

    Node *parentNode = parentPosition.node;
    Node *newNode = new Node(value);
    newNode->parent = parentNode;

    if (parentNode->firstChild == nullptr) {
      parentNode->firstChild = newNode;
    } else {
      Node *cursor = parentNode->firstChild;
      while (cursor->nextSibling != nullptr) {
        cursor = cursor->nextSibling;
      }
      cursor->nextSibling = newNode;
    }

    nodeCount++;
    return Position(newNode);
  }

  // Returns direct children positions for a node.
  vector<Position> children(Position position) {
    vector<Position> result;
    if (position.isNull()) {
      return result;
    }

    Node *child = position.node->firstChild;
    while (child != nullptr) {
      result.push_back(Position(child));
      child = child->nextSibling;
    }
    return result;
  }

  // Returns preorder list of all positions.
  vector<Position> preorder() {
    vector<Position> result;
    vector<Node *> raw;
    collectPreorder(rootNode, raw);
    for (int i = 0; i < (int)raw.size(); i++) {
      result.push_back(Position(raw[i]));
    }
    return result;
  }
};

#endif
