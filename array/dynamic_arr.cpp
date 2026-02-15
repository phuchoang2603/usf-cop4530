#include <iostream>
using namespace std;

class DynamicArray {
private:
  int *arr;
  int length;
  int capacity;

  // When array is full
  void resize() {
    // create a bigger arr
    capacity = 2 * capacity;
    int *newArr = new int[capacity];

    // copy old elements
    for (int i = 0; i < length; i++) {
      newArr[i] = arr[i];
    }

    // delete old memory
    delete[] arr;

    // update pointer
    arr = newArr;
  }

public:
  // Initialization
  DynamicArray(int cap = 2) {
    capacity = cap;
    length = 0;
    arr = new int[capacity];
  }

  int getLength() { return length; }

  int getElement(int index) {
    // Checks for valid index
    if (index < 0 || index >= length) {
      cout << "Index out of bounds!" << endl;
      return -1;
    }
    return arr[index];
  }

  void append(int value) {
    // Resize only when full
    if (length == capacity) {
      resize();
    }

    arr[length] = value;
    length++;
  }

  void display() {
    for (int i = 0; i < length; i++) {
      cout << arr[i] << " ";
    }

    cout << endl;
  }
};

int main() {
  DynamicArray a;

  a.append(50);
  a.append(60);
  a.append(70);

  a.display();
}
