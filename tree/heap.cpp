#include <utility>
#include <vector>
using namespace std;

class MaxHeap {
private:
  vector<int> data;

  void bubbleUp(int i) {
    while (i > 0) {
      int parent = (i - 1) / 2;

      if (data[parent] >= data[i]) {
        break;
      }

      swap(data[parent], data[i]);
      i = parent;
    }
  }

  void bubbleDown(int i) {
    int n = data.size();
    while (true) {
      int left = 2 * i + 1;
      int right = 2 * i + 2;
      int largest = i;

      if (left < n && data[left] > data[largest]) {
        largest = left;
      }

      if (right < n && data[right] > data[largest]) {
        largest = right;
      }

      if (largest != i) {
        // Found larger child
        swap(data[i], data[largest]);
        i = largest;
      } else {
        // Complete bubble down
        break;
      }
    }
  }

public:
  int peek() { return data.front(); }
  void insert(int value) {
    data.push_back(value);
    bubbleUp(data.size() - 1);
  }

  void removeRoot() {
    if (data.empty()) {
      return;
    }

    data[0] = data.back();
    data.pop_back();

    bubbleDown(0);
  }
};
