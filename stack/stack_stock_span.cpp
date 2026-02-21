#include <cstddef>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
  vector<int> prices = {60, 80, 90, 70, 60, 75, 185};
  vector<int> ans(prices.size());
  stack<int> higher_prices;

  for (size_t i = 0; i < prices.size(); i++) {
    while (higher_prices.size() > 0 &&
           prices[higher_prices.top()] < prices[i]) {
      higher_prices.pop();
    }

    if (higher_prices.size() == 0) {
      ans[i] = i + 1;
    } else {
      ans[i] = i - higher_prices.top();
    }

    higher_prices.push(i);
  }

  for (size_t i = 0; i < ans.size(); i++) {
    cout << ans[i] << " ";
  }

  return 0;
}
