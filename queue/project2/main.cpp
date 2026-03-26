#include <iostream>
#include <limits>
#include <string>

#include "registration_queue_system.h"

using namespace std;

// Reads an integer safely from standard input.
int readInt() {
  int value;
  while (!(cin >> value)) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter a valid number: ";
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return value;
}

// Reads a full line of text with a prompt.
string readText(string prompt) {
  string value;
  cout << prompt;
  getline(cin, value);
  return value;
}

// Prints the interactive program menu.
void printMenu() {
  cout << "\nClass Registration Queue" << endl;
  cout << "1) Add undergraduate" << endl;
  cout << "2) Add graduate" << endl;
  cout << "3) Process next student" << endl;
  cout << "4) Show next student" << endl;
  cout << "5) Show queue size" << endl;
  cout << "0) Exit" << endl;
  cout << "Choice: ";
}

int main() {
  RegistrationQueueSystem registration;
  bool running = true;

  while (running) {
    printMenu();
    int choice = readInt();

    switch (choice) {
    case 1: {
      string name = readText("Name: ");
      string id = readText("Student ID: ");
      cout << "Year (1-4): ";
      int year = readInt();
      registration.addStudent(UNDERGRAD, name, id, year, "");
      break;
    }
    case 2: {
      string name = readText("Name: ");
      string id = readText("Student ID: ");
      string programType = readText("Program type (MS or PhD): ");
      registration.addStudent(GRAD, name, id, 0, programType);
      break;
    }
    case 3:
      registration.processNext();
      break;
    case 4:
      registration.showNext();
      break;
    case 5:
      registration.showCount();
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
