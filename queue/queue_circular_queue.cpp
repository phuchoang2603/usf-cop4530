#include <iostream>
using namespace std;

class CircularQueue {
  int *arr;
  int front;
  int rear;
  int size;

public:
  CircularQueue(int n) {
    size = n;
    arr = new int[size];
    front = -1;
    rear = -1;
  }

  bool empty() { return front == -1; }

  void push(int val) {
    if ((rear + 1) % size == front) {
      cout << "Queue is full" << endl;
      return;
    }

    if (empty()) {
      front = rear = 0;
    } else {
      rear = (rear + 1) % size;
    }

    arr[rear] = val;
  }

  void pop() {
    if (empty()) {
      cout << "Queue is empty" << endl;
      return;
    }

    if (front == rear) {
      front = rear = -1;
    } else {
      front = (front + 1) % size;
    }
  }

  int frontValue() {
    if (empty()) {
      cout << "Queue is empty" << endl;
      return -1;
    }

    return arr[front];
  }

  int rearValue() {
    if (empty()) {
      cout << "Queue is empty" << endl;
      return -1;
    }

    return arr[rear];
  }
};

int main() {
  CircularQueue q(5);

  for (int i = 0; i < 6; i++) {
    q.push(i);
  }

  cout << "Front: " << q.frontValue() << endl;
  cout << "Rear: " << q.rearValue() << endl;

  q.pop();

  cout << "Front: " << q.frontValue() << endl;
  cout << "Rear: " << q.rearValue() << endl;

  return 0;
}
