#include <iostream>
#include <vector>

extern "C" {
#include <stdlib.h>
}

using namespace std;

extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
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

  // Call the global variable initializer
  __cxx_global_var_init();

  return 0;
}

int main() {
  return 0;
}