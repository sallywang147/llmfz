#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hermes/hermes.h"
#include "hermes/vm/Callable.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    hermes::vm::initializeHermesVM();
    initialized = true;
  }
  auto runtime = hermes::makeHermesRuntime();
  auto args = hermes::vm::NativeArgs::create(runtime);
  hermes::vm::createDynamicFunction(runtime.get(), args.get(), 0);
  return 0;
}