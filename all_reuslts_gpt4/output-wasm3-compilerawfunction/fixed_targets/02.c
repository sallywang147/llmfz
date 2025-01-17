#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "m3.h"
#include "m3_module.h"
#include "m3_function.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize M3Module and M3Function
  M3Module module;
  M3Function function;

  // Consume data for two strings
  std::string str1 = stream.ConsumeRandomLengthString();
  std::string str2 = stream.ConsumeRandomLengthString();

  // Call the target function
  CompileRawFunction(&module, &function, const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()));

  return 0;
}