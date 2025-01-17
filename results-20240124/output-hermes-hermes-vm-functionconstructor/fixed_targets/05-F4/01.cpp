#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "hermes/hermes.h"
#include "hermes/vm/Runtime.h"
#include "hermes/vm/NativeArgs.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string s = stream.ConsumeRemainingBytesAsString();
  hermes::vm::Runtime* runtime = hermes::vm::Runtime::create(hermes::vm::RuntimeConfig::Builder().build());
  hermes::vm::NativeArgs* args = new hermes::vm::NativeArgs();
  hermes::vm::functionConstructor(const_cast<char*>(s.c_str()), runtime, args);
  runtime->run();
  delete runtime;
  delete args;
  return 0;
}