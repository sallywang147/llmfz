#include <iostream>
#include <vector>

extern "C" {
#include <stdlib.h>
}

using namespace std;

int main() {
  vector<int> v;
  for (int i = 0; i < 10; i++) {
    v.push_back(rand());
  }
  for (int i = 0; i < 10; i++) {
    cout << v[i] << endl;
  }
  return 0;
}