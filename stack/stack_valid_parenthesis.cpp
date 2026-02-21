#include <cstddef>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool validParenthesis(string s) {
  stack<char> characters;

  for (size_t i = 0; i < s.length(); i++) {
    if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
      characters.push(s[i]);
    } else if (s[i] == ')' || s[i] == '}' || s[i] == ']') {
      if (characters.empty()) {
        return false;
      }

      char topChar = characters.top();

      if ((s[i] == ')' && topChar == '(') || (s[i] == '}' && topChar == '{') ||
          (s[i] == ']' && topChar == '[')) {
        characters.pop();
      } else {
        return false;
      }
    } else {
      continue;
    }
  }

  return characters.empty();
}

int main() {
  string s = "(((({{{ hello }}}))))";

  cout << validParenthesis(s) << endl;

  return 0;
}
