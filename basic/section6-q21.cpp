#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
  double numerator, denominator;

  cout << "Enter numerator: ";
  cin >> numerator;
  cout << "Enter denominator: ";
  cin >> denominator;

  try {
    if (denominator == 0) {
      throw "Error: Division by zero is not allowed.";
    }

    double result = numerator / denominator;
    cout << "Result: " << result << endl;
  } catch (const char *errorMessage) {
    cout << errorMessage << endl;
  }

  return EXIT_SUCCESS;
}
