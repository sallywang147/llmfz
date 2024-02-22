#include <iostream>
#include <vector>

extern "C" {
#include <stdio.h>
#include <stdlib.h>
}

using namespace std;

int main() {
  // Create a vector of integers
  vector<int> numbers;

  // Add some numbers to the vector
  numbers.push_back(1);
  numbers.push_back(2);
  numbers.push_back(3);

  // Print the numbers in the vector
  for (int i = 0; i < numbers.size(); i++) {
    cout << numbers[i] << endl;
  }

  return 0;
}