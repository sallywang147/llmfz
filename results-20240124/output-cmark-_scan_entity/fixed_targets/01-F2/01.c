#include <iostream>
#include <string>

using namespace std;

extern "C" {
#include "scan_entity.h"
}

int main() {
  char str[] = "This is a string";
  _scan_entity(str);
  return 0;
}