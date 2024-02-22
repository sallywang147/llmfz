#include <hermes/hermes.h>

extern "C" {
#include "hermes/vm/function-constructor.h"
}

int main() {
  hermes::vm::Runtime runtime;
  hermes::vm::functionConstructor("myFunction", &runtime, nullptr);
  return 0;
}