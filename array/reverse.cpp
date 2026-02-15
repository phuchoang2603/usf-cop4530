#include <iostream>

void reverseArray(int *arr, int length) {
  int *p = arr;
  int *q = arr + length - 1;
  int temp = 0;

  for (; p < q; p++, q--) {
    temp = *p;
    *p = *q;
    *q = temp;
  }
}

int main() {
  int arr[4] = {10, 20, 30, 40};
  int length = 4;

  reverseArray(arr, length);

  for (int i = 0; i < length; i++) {
    std::cout << arr[i] << " ";
  }
}
