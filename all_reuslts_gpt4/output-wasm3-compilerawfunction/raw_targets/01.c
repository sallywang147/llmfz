#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "m3.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the M3 environment
  IM3Environment env = m3_NewEnvironment ();
  if (!env) {
    return 0;
  }

  // Create a new M3 module
  IM3Module module = m3_NewModule (env);
  if (!module) {
    m3_FreeEnvironment(env);
    return 0;
  }

  // Create a new M3 function
  IM3Function function = m3_NewFunction(module, "fuzzFunc", "()");
  if (!function) {
    m3_FreeModule(module);
    m3_FreeEnvironment(env);
    return 0;
  }

  // Consume data to use as input for the function
  std::string input1 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string input2 = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  CompileRawFunction(module, function, const_cast<char*>(input1.c_str()), const_cast<char*>(input2.c_str()));

  // Cleanup
  m3_FreeFunction(function);
  m3_FreeModule(module);
  m3_FreeEnvironment(env);

  return 0;
}