#include <iostream>
#include <fstream>

extern "C" {
#include "flex.h"
}

int main() {
  std::ifstream in("input.txt");
  yyin = &in;
  yylex();
  return 0;
}