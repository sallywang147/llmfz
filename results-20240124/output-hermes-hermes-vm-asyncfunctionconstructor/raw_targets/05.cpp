 #include <cstdint>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

#include "hermes/hermes.h"
#include "hermes/vm/GC.h"
#include "hermes/vm/Runtime.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (!size) {
    // Hermes can't handle empty input, and it would have a performance cost
    // to do so.
    return 0;
  }
  // Hermes bytecode is assumed to be trusted, and there are often no checks
  // for validity (for performance purposes).
  // Discard inputs that would be interpreted as bytecode to avoid reporting
  // those as errors.
  if (hermes::vm::HermesRuntime::isHermesBytecode(data, size)) {
    return 0;
  }

  std::string s(reinterpret_cast<const char *>(data), size);
  s.append("\0");
  hermes::vm::Runtime runtime;
  hermes::vm::GC gc(runtime);
  hermes::vm::NativeArgs args(runtime);
  hermes::vm::asyncFunctionConstructor(nullptr, &runtime, &args);
  return 0;
}