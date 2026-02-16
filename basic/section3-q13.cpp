#include <cstdlib>
#include <iostream>

using namespace std;

// Function definition using pass-by-reference (int &)
void swapInts(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

int main() {
  int x = 100;
  int y = 200;

  cout << "Before swap: x = " << x << ", y = " << y << endl;

  // Call the function
  swapInts(x, y);

  cout << "After swap:  x = " << x << ", y = " << y << endl;

  return EXIT_SUCCESS;
}
