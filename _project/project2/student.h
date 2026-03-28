#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

const int UNDERGRAD = 1;
const int GRAD = 2;

class Student {
protected:
  string name;
  string id;

public:
  // Builds a base student with name and student id.
  Student(string studentName, string studentId)
      : name(studentName), id(studentId) {}

  // Virtual destructor for safe polymorphic cleanup.
  virtual ~Student() {}

  // Returns the student level string.
  virtual string level() = 0;

  // Returns the student's registration priority label.
  virtual string priorityTag() = 0;

  // Returns formatted student information.
  string info() {
    return name + " (" + id + ") - " + level() + " - " + priorityTag();
  }
};

class UndergradStudent : public Student {
private:
  int year;

public:
  // Builds an undergraduate student with class year.
  UndergradStudent(string studentName, string studentId, int studentYear)
      : Student(studentName, studentId), year(studentYear) {}

  // Returns the fixed level text for undergrads.
  string level() { return "Undergraduate"; }

  // Returns priority based on undergraduate year.
  string priorityTag() {
    if (year >= 4) {
      return "Senior priority";
    }
    return "Regular priority";
  }
};

class GradStudent : public Student {
private:
  string programType;

public:
  // Builds a graduate student with program type.
  GradStudent(string studentName, string studentId, string studentProgramType)
      : Student(studentName, studentId), programType(studentProgramType) {}

  // Returns the fixed level text for grads.
  string level() { return "Graduate"; }

  // Returns priority based on graduate program type.
  string priorityTag() {
    if (programType == "PhD" || programType == "phd") {
      return "Research priority";
    }
    return "Standard grad priority";
  }
};

#endif
