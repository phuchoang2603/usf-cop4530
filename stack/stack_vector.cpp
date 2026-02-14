#include <iostream>
#include <vector>
using namespace std;

class Stackvec {
  vector<int> v;

public:
  void push(int data) { v.push_back(data); }

  void pop() { v.pop_back(); }

  void top() { cout << v[v.size() - 1] << endl; }

  bool empty() { return v.size() == 0; }
};

int main() {
  Stackvec s;

  s.push(50);
  s.push(60);
  s.push(70);

  while (!s.empty()) {
    s.top();
    s.pop();
  }

  cout << (s.empty() ? "Stack is empty" : "Stack is not empty") << endl;
}
