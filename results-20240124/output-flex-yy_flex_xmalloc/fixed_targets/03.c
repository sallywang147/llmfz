#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

extern "C" {
#include "flex.h"
}

using namespace std;

int main() {
  ifstream in("input.txt");
  if (!in) {
    cerr << "Cannot open input file" << endl;
    return 1;
  }

  yylex();

  return 0;
}