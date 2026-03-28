#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
  int number = 42;

  int *ptr;

  // &number retrieves the location where number is stored
  // so it can be assigned to ptr
  ptr = &number;

  // *ptr looks at the address stored in ptr
  // and retrieves the value 42
  cout << "Value of number via pointer: " << *ptr << endl;

  return EXIT_SUCCESS;
}
