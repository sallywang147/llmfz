 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "hermes/hermes.h"
#include "hermes/vm/Runtime.h"
#include "hermes/vm/NativeArgs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string s = stream.ConsumeRemainingBytesAsString();
  hermes::vm::Runtime* runtime = new hermes::vm::Runtime();
  hermes::vm::NativeArgs* args = new hermes::vm::NativeArgs();
  hermes::vm::functionConstructor(const_cast<char*>(s.c_str()), runtime, args);
  delete runtime;
  delete args;
  return 0;
}