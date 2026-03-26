#ifndef QUEUE_H
#define QUEUE_H

template <typename T> class CircularQueue {
private:
  struct Node {
    T data;
    Node *next;
    Node(T value) : data(value), next(nullptr) {}
  };

  Node *rearNode;
  int currentSize;

public:
  // Initializes an empty circular queue.
  CircularQueue() : rearNode(nullptr), currentSize(0) {}

  // Frees all nodes still stored in the queue.
  ~CircularQueue() {
    while (!isEmpty()) {
      dequeue();
    }
  }

  // Returns true when the queue has no elements.
  bool isEmpty() { return currentSize == 0; }

  // Returns the number of elements in the queue.
  int size() { return currentSize; }

  // Returns the front element without removing it.
  T front() {
    if (isEmpty()) {
      return T();
    }
    return rearNode->next->data;
  }

  // Adds a new element to the rear of the queue.
  void enqueue(T value) {
    Node *newNode = new Node(value);

    if (isEmpty()) {
      newNode->next = newNode;
      rearNode = newNode;
      currentSize++;
      return;
    }

    newNode->next = rearNode->next;
    rearNode->next = newNode;
    rearNode = newNode;
    currentSize++;
  }

  // Removes and returns the front element.
  T dequeue() {
    if (isEmpty()) {
      return T();
    }

    Node *front = rearNode->next;
    T value = front->data;

    if (front == rearNode) {
      rearNode = nullptr;
    } else {
      rearNode->next = front->next;
    }

    delete front;
    currentSize--;
    return value;
  }
};

#endif
