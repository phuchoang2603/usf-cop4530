// Inheritance graph:
// Person
// ├── Student
// │   ├── UndergradStudent
// │   └── GradStudent
// └── Faculty
//     ├── Professor
//     └── Instructor

#include <string>
#include <vector>

using namespace std;

class Person {
protected:
  string name;
  int age;

public:
  Person(const string &name, int age) : name(name), age(age) {}
};

class Student : public Person {
protected:
  string studentId;
  double gpa;

public:
  Student(const string &name, int age, const string &studentId, double gpa)
      : Person(name, age), studentId(studentId), gpa(gpa) {}
};

class UndergradStudent : public Student {
  string major;

public:
  UndergradStudent(const string &name, int age, const string &studentId,
                   double gpa, const string &major)
      : Student(name, age, studentId, gpa), major(major) {}
};

class GradStudent : public Student {
  string researchTopic;

public:
  GradStudent(const string &name, int age, const string &studentId, double gpa,
              const string &researchTopic)
      : Student(name, age, studentId, gpa), researchTopic(researchTopic) {}
};

class Faculty : public Person {
protected:
  string facultyId;
  string department;

public:
  Faculty(const string &name, int age, const string &facultyId,
          const string &department)
      : Person(name, age), facultyId(facultyId), department(department) {}
};

class Professor : public Faculty {
  string researchTopic;
  vector<string> classesTaught;

public:
  Professor(const string &name, int age, const string &facultyId,
            const string &department, const string &researchTopic,
            const vector<string> &classesTaught)
      : Faculty(name, age, facultyId, department), researchTopic(researchTopic),
        classesTaught(classesTaught) {}
};

class Instructor : public Faculty {
  vector<string> classesTaught;

public:
  Instructor(const string &name, int age, const string &facultyId,
             const string &department, const vector<string> &classesTaught)
      : Faculty(name, age, facultyId, department),
        classesTaught(classesTaught) {}
};
