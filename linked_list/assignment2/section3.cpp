#include <iostream>
#include <string>

using namespace std;

template <typename T1, typename T2> class Pair {
  T1 first;
  T2 second;

public:
  Pair(T1 f, T2 s) : first(f), second(s) {}

  void print() const {
    cout << "Pair: [" << first << ", " << second << "]" << endl;
  }
};

int main() {
  Pair<int, string> pair1(42, "Answers");
  pair1.print();

  Pair<float, long> pair2(3.14f, 987654321L);
  pair2.print();

  Pair<double, char> pair3(99.99, 'A');
  pair3.print();

  Pair<string, string> pair4("Hello", "World");
  pair4.print();

  Pair<bool, int> pair5(true, 100);
  pair5.print();

  return 0;
}
