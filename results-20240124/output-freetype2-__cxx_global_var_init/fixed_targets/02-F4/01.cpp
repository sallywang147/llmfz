#include <iostream>
#include <vector>

extern "C" {
  void __cxx_global_var_init();
}

int main() {
  __cxx_global_var_init();
  std::vector<int> v;
  v.push_back(1);
  std::cout << v[0] << std::endl;
  return 0;
}