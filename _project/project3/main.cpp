#include <iostream>
#include <string>

#include "decision_tree.h"

using namespace std;

// Converts string to integer if valid.
bool parseInt(string text, int &value) {
  if (text.size() == 0) {
    return false;
  }

  int start = 0;
  if (text[0] == '-') {
    if (text.size() == 1) {
      return false;
    }
    start = 1;
  }

  for (int i = start; i < (int)text.size(); i++) {
    if (text[i] < '0' || text[i] > '9') {
      return false;
    }
  }

  value = stoi(text);
  return true;
}

// Prints the initial tree selection menu.
void printTreeMenu() {
  cout << "Choose a decision tree:" << endl;
  cout << "1 - Investment Advice Decision Tree" << endl;
  cout << "2 - Car Purchase Decision Tree" << endl;
  cout << "Choice: ";
}

// Reads user choice and returns the matching input file name.
bool getInputFile(string &inputFile) {
  printTreeMenu();

  string choiceInput;
  getline(cin, choiceInput);

  int choice = 0;
  if (!parseInt(choiceInput, choice)) {
    return false;
  }

  switch (choice) {
  case 1:
    inputFile = "tree-investment-1.txt";
    return true;
  case 2:
    inputFile = "tree-car.txt";
    return true;
  default:
    return false;
  }
}

// Runs interactive node exploration loop.
void runExplorer(DecisionTree &tree) {
  while (true) {
    cout << "Which node would you like to explore (enter position or "
            "\"exit\"): ";
    string input;
    getline(cin, input);

    if (input == "exit") {
      cout << "Goodbye!" << endl;
      break;
    }

    int position = 0;
    if (!parseInt(input, position) || !tree.hasPosition(position)) {
      cout << "Invalid input. Please try again." << endl;
      continue;
    }

    cout << "Node's content: " << tree.nodeContent(position) << endl;
    cout << "Ancestor: " << tree.oneAncestor(position) << endl;
    cout << "Descendant: " << tree.oneDescendant(position) << endl;
    cout << "Sibling: " << tree.oneSibling(position) << endl;
  }
}

int main() {
  string inputFile = "";
  if (!getInputFile(inputFile)) {
    cout << "Invalid input. Please try again." << endl;
    return 0;
  }

  DecisionTree tree;
  if (!tree.buildFromFile(inputFile)) {
    cout << "Unable to build tree from input file." << endl;
    return 0;
  }

  if (!tree.writeAboutTree("about_tree.txt")) {
    cout << "Unable to write about_tree.txt." << endl;
    return 0;
  }

  runExplorer(tree);
  return 0;
}
