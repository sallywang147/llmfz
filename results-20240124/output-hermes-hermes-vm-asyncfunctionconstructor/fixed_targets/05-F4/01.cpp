#include <hermes/hermes.h>
#include <hermes/hermes.h>
#include <hermes/hermes.h>
#include <hermes/hermes.h>

extern "C" {
#include <hermes/hermes.h>
#include <hermes/hermes.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  hermes::vm::Runtime runtime;
  hermes::vm::NativeArgs args;
  hermes::vm::asyncFunctionConstructor((char *)data, &runtime, &args);
  return 0;
}