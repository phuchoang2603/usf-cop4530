#include <cstdlib>
#include <iostream>

using namespace std;

class Rectangle {
private:
  double length;
  double width;

public:
  void setValues(double l, double w) {
    length = l;
    width = w;
  }

  double getArea() { return length * width; }

  double getPerimeter() { return 2 * (length + width); }
};

int main() {
  Rectangle rect;

  rect.setValues(5.0, 10.0);

  cout << "Area: " << rect.getArea() << endl;
  cout << "Perimeter: " << rect.getPerimeter() << endl;

  return EXIT_SUCCESS;
}
