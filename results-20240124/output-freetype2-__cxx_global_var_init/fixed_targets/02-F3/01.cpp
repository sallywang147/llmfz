#include <iostream>

extern "C" {
#include <vector>
}

int main() {
  std::vector<int> v;
  v.push_back(1);
  std::cout << v[0] << std::endl;
  return 0;
}