#include <cstdlib>
#include <iostream>

using namespace std;

// Function taking a const parameter
void printNumbers(const int limit) {
  for (int i = 1; i <= limit; i++) {
    cout << i << " ";
  }
  cout << endl;
}

int main() {
  // A constant variable
  const int MAX_COUNT = 5;

  cout << "Printing up to " << MAX_COUNT << ":" << endl;

  printNumbers(MAX_COUNT);

  return EXIT_SUCCESS;
}
