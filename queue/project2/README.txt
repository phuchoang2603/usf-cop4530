Project: Office Hour Waiting Line (Queue)

Group Members

- Felix Hoang
- Hoang Nam Tran

Files:
- main.cpp

How to compile on the student cluster:
1) Open terminal in this folder.
2) Run:
   g++ -std=c++11 main.cpp -o project2

How to run:
1) Run:
   ./project2
2) Use the menu options:
   - Add student to line (enqueue)
   - Help next student (dequeue)
   - Display full line

Notes:
- Queue is implemented as a templated circularly linked list in main.cpp.
- Inheritance is demonstrated with Person (base class) and Student (derived class).
