#include <iostream>
#include <cstdio>
#include <cstring>
extern "C" {
#include "llvm/Fuzz.h"
}

int main(int argc, char** argv) {
  LLVMFuzzerTestOneInput(argv[1], strlen(argv[1]));
  return 0;
}