## Section 1: Basic Syntax and Data Types (15 points)

### 1. (3 pts) Explain the purpose of the main() function in a C++ program.

The `main()` function serves as the starting point for execution in every C++ program. When a user runs an executable, the operating system loads the program into memory and begins execution from this function. It also returns an integer value to the operating system to indicate whether the program ended successfully.

### 2. (4 pts) List four fundamental data types in C++ and briefly describe each.

### 4. (4 pts) Explain the difference between float and double. Include one situation where double is preferred.

- **Difference:** `float` represents a single-precision floating-point number, while `double` represents a double-precision floating-point number. The exact size depends on the implementation, but `double` typically offers more precision than `float`.
- **Preference:** `double` is preferred when **more accuracy** is required for calculations. Additionally, default floating-point literals in C++ (e.g., `3.14`) are treated as `double` by default, making it a standard choice for general floating-point arithmetic.

## Section 2: Control Structures (20 points)

### 6. (5 pts) Explain the difference between a while loop and a do-while loop. Include a short code snippet for each.

**Difference:**

- **`while` loop:** This is an **entry-controlled** loop. The condition is evaluated _before_ the loop body executes. If the condition is false initially, the loop body never runs.

```cpp
int i = 0;
while (i < 5) {
    cout << i << " ";
    i++;
}
```

- **`do-while` loop:** This is an **exit-controlled** loop. The loop body executes first, and then the condition is evaluated. This guarantees that the loop body runs **at least once**, regardless of whether the condition is true or false.

```cpp
int i = 0;
do {
    cout << i << " ";
    i++;
} while (i < 5);
```

### 8. (5 pts) Write a C++ program using a switch statement to display the day of the week.

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    int day;
    cout << "Enter a number (1-7): ";
    cin >> day;

    switch (day) {
        case 1:
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
            cout << "Wednesday" << endl;
            break;
        case 4:
            cout << "Thursday" << endl;
            break;
        case 5:
            cout << "Friday" << endl;
            break;
        case 6:
            cout << "Saturday" << endl;
            break;
        case 7:
            cout << "Sunday" << endl;
            break;
        default:
            cout << "Invalid input! Please enter a number between 1 and 7." << endl;
    }

    return EXIT_SUCCESS;
}
```

## Section 3: Functions (20 points)
