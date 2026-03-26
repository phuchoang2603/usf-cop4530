#ifndef REGISTRATION_QUEUE_SYSTEM_H
#define REGISTRATION_QUEUE_SYSTEM_H

#include <iostream>
#include <string>

#include "queue.h"
#include "student.h"

using namespace std;

class RegistrationQueueSystem {
private:
  CircularQueue<Student *> waitList;

public:
  // Cleans up all remaining students in the queue.
  ~RegistrationQueueSystem() {
    while (!waitList.isEmpty()) {
      Student *student = waitList.dequeue();
      delete student;
    }
  }

  // Creates and enqueues a student based on the selected type.
  void addStudent(int studentType, string name, string id, int year,
                  string programType) {
    Student *student;

    if (studentType == UNDERGRAD) {
      student = new UndergradStudent(name, id, year);
    } else {
      student = new GradStudent(name, id, programType);
    }

    waitList.enqueue(student);
    cout << "Added: " << student->info() << endl;
  }

  // Processes and removes the next student from the queue.
  void processNext() {
    if (waitList.isEmpty()) {
      cout << "Queue is empty." << endl;
      return;
    }

    Student *student = waitList.dequeue();
    cout << "Processing registration for: " << student->info() << endl;
    delete student;
  }

  // Displays the next student without removing them.
  void showNext() {
    if (waitList.isEmpty()) {
      cout << "Queue is empty." << endl;
      return;
    }

    Student *student = waitList.front();
    cout << "Next student: " << student->info() << endl;
  }

  // Displays the current number of students in queue.
  void showCount() { cout << "Students in queue: " << waitList.size() << endl; }
};

#endif
