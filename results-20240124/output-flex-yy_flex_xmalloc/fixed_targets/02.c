#include <iostream>
#include <fstream>

extern "C" {
#include "flex.h"
}

int main() {
  std::ifstream input("input.txt");
  yylex();
  return 0;
}