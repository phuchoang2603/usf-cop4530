#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
  int num1, num2;

  cout << "Enter two numbers: ";
  cin >> num1 >> num2;

  int sum = num1 + num2;

  cout << "Sum: " << sum << endl;

  return EXIT_SUCCESS;
}
