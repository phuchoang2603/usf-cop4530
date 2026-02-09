#include <iostream>
#include <stdexcept>
using namespace std;

class Stackarr {
  int arr[5];
  int topindex;

public:
  Stackarr() { topindex = 0; }

  void push(int data) {
    if (topindex == 5) {
      throw runtime_error("Stack is full");
    }
    arr[topindex] = data;
    topindex++;
  }

  void pop() {
    if (topindex == 0) {
      throw runtime_error("Stack is empty");
    }
    topindex--;
  }

  void top() { cout << arr[topindex - 1] << endl; }

  bool empty() { return topindex == 0; }
};

int main() {
  Stackarr s;

  s.push(50);
  s.push(60);
  s.push(70);

  while (!s.empty()) {
    s.top();
    s.pop();
  }

  cout << (s.empty() ? "Stack is empty" : "Stack is not empty") << endl;
}
