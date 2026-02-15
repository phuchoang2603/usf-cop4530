#include <iostream>

int deleteEvenIdx(int *arr, int length) {
  int *p = arr;

  for (int i = 0; i < length; i++) {
    if (i % 2 == 1) {
      *p = arr[i];
      p++;
    }
  }

  return p - arr;
}

int main() {
  int arr[6] = {10, 20, 30, 40, 50, 60};
  int length = 6;

  int new_length = deleteEvenIdx(arr, length);

  for (int i = 0; i < new_length; i++) {
    std::cout << arr[i] << " ";
  }
}
