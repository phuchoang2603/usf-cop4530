#include <iostream>

using namespace std;

enum DayOfWeek {
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  SUNDAY
};

int main() {
  int dayNum;

  cout << "Enter a day number (0-6): ";
  cin >> dayNum;

  DayOfWeek day = static_cast<DayOfWeek>(dayNum);

  if (day == MONDAY) {
    cout << "Monday" << endl;
  } else if (day == TUESDAY) {
    cout << "Tuesday" << endl;
  } else if (day == WEDNESDAY) {
    cout << "Wednesday" << endl;
  } else if (day == THURSDAY) {
    cout << "Thursday" << endl;
  } else if (day == FRIDAY) {
    cout << "Friday" << endl;
  } else if (day == SATURDAY) {
    cout << "Saturday" << endl;
  } else if (day == SUNDAY) {
    cout << "Sunday" << endl;
  } else {
    cout << "Invalid day number" << endl;
  }

  return EXIT_SUCCESS;
}
