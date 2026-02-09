#include <iostream>
#include <stack>
using namespace std;

int main() {
  stack<int> s;

  s.push(50);
  s.push(60);
  s.push(70);

  while (!s.empty()) {
    cout << s.top() << endl;
    s.pop();
  }

  cout << s.empty() << endl;
}
