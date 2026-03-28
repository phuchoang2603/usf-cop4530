#include <iostream>
using namespace std;

class Object {
public:
  virtual void printMe() const = 0;
};

class Place : public Object {
public:
  void printMe() const override { cout << "Buy it.\n" << endl; }
};

class Region : public Place {
public:
  void printMe() const override { cout << "Box it.\n" << endl; }
};

class State : public Region {
public:
  void printMe() const override { cout << "Ship it.\n" << endl; }
};

class Maryland : public State {
public:
  void printMe() const override { cout << "Read it.\n" << endl; }
};

int main() {
  Region *mid = new State;
  State *md = new Maryland;
  Object *obj = new Place;
  Place *usa = new Region;

  md->printMe();  // Read it. (since md points to a Maryland object)
  mid->printMe(); // Ship it. (since mid points to a State object)

  (dynamic_cast<Place *>(obj))->printMe();
  // Buy it. (obj points from Place to a Place object. Cast is valid.)

  obj = md;

  (dynamic_cast<Maryland *>(obj))->printMe();
  // Read it. (obj now points from Maryland to the Maryland object. Cast is
  // valid.)

  obj = usa;

  (dynamic_cast<Place *>(obj))->printMe();
  // Box it.
  // usa originally pointed to a Region object. Even if casting
  // the pointer to Place*, the underlying object is still a Region.
  // Because printMe() is virtual, the Region version is called.

  usa = md;

  (dynamic_cast<Place *>(usa))->printMe();
  // Read it.
  // usa now points to md, which is a Maryland object. The cast to
  // Place* is valid, but dynamic dispatch ensures the Maryland version
  // of the virtual function is what actually executes.

  return 0;
}
