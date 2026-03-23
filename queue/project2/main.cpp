#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <typename T> class CircularQueue {
private:
  struct Node {
    T data;
    Node *next;
    explicit Node(const T &value) : data(value), next(nullptr) {}
  };

  Node *rearNode;
  int currentSize;

public:
  CircularQueue() : rearNode(nullptr), currentSize(0) {}

  ~CircularQueue() { clear(); }

  bool isEmpty() const { return currentSize == 0; }

  int size() const { return currentSize; }

  void enqueue(const T &value) {
    Node *newNode = new Node(value);
    if (isEmpty()) {
      newNode->next = newNode;
      rearNode = newNode;
    } else {
      newNode->next = rearNode->next;
      rearNode->next = newNode;
      rearNode = newNode;
    }
    currentSize++;
  }

  T dequeue() {
    if (isEmpty()) {
      throw out_of_range("Queue is empty.");
    }

    Node *frontNode = rearNode->next;
    T removedValue = frontNode->data;

    if (frontNode == rearNode) {
      rearNode = nullptr;
    } else {
      rearNode->next = frontNode->next;
    }

    delete frontNode;
    currentSize--;
    return removedValue;
  }

  vector<T> toVector() const {
    vector<T> items;
    if (isEmpty()) {
      return items;
    }

    Node *current = rearNode->next;
    for (int i = 0; i < currentSize; i++) {
      items.push_back(current->data);
      current = current->next;
    }
    return items;
  }

  void clear() {
    while (!isEmpty()) {
      dequeue();
    }
  }
};

class Person {
protected:
  string name;
  string netId;

public:
  Person(const string &personName, const string &personNetId)
      : name(personName), netId(personNetId) {}
  virtual ~Person() {}
  virtual string getDescription() const = 0;
};

class Student : public Person {
private:
  string topic;

public:
  Student(const string &studentName, const string &studentNetId,
          const string &studentTopic)
      : Person(studentName, studentNetId), topic(studentTopic) {}

  string getDescription() const override {
    return name + " (" + netId + ") - Topic: " + topic;
  }
};

class OfficeHourLine {
private:
  CircularQueue<Student> waitingLine;

public:
  void addStudentToLine(const string &name, const string &netId,
                        const string &topic) {
    waitingLine.enqueue(Student(name, netId, topic));
    cout << "Added: " << name << endl;
  }

  void helpNextStudent() {
    try {
      Student nextStudent = waitingLine.dequeue();
      cout << "Helping: " << nextStudent.getDescription() << endl;
    } catch (const out_of_range &) {
      cout << "No students in line." << endl;
    }
  }

  void displayLine() const {
    vector<Student> students = waitingLine.toVector();
    if (students.empty()) {
      cout << "Line is empty." << endl;
      return;
    }

    cout << "Current line:" << endl;
    for (int i = 0; i < static_cast<int>(students.size()); i++) {
      cout << i + 1 << ". " << students[i].getDescription() << endl;
    }
  }
};

void printMenu() {
  cout << "\nOffice Hour Queue" << endl;
  cout << "1) Add student" << endl;
  cout << "2) Help next student" << endl;
  cout << "3) Display line" << endl;
  cout << "0) Exit" << endl;
  cout << "Choose: ";
}

int readInt() {
  int value;
  while (!(cin >> value)) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Please enter a number: ";
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return value;
}

int main() {
  OfficeHourLine officeHourLine;
  bool running = true;

  while (running) {
    printMenu();
    int choice = readInt();

    switch (choice) {
    case 1: {
      string name;
      string netId;
      string topic;

      cout << "Student name: ";
      getline(cin, name);
      cout << "NetID: ";
      getline(cin, netId);
      cout << "Topic: ";
      getline(cin, topic);

      officeHourLine.addStudentToLine(name, netId, topic);
      break;
    }
    case 2:
      officeHourLine.helpNextStudent();
      break;
    case 3:
      officeHourLine.displayLine();
      break;
    case 0:
      running = false;
      break;
    default:
      cout << "Invalid option." << endl;
      break;
    }
  }

  return 0;
}
