#include <iostream>
#include <string>

// Fix the build issue by wrapping the header include with extern "C" {}
extern "C" {
#include "RegularCommandService.h"
}

using namespace std;

int main() {
  RegularCommandService service;
  service.execute();
  return 0;
}