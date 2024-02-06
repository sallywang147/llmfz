#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "iec61850_server.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a MmsValue object
  MmsValue* value = MmsValue_newIntegerFromInt32(stream.ConsumeIntegral<int32_t>());
  if (value == nullptr) {
    return 0;
  }

  // Create a buffer for the output
  std::vector<char> buffer(stream.remaining_bytes());

  // Call the function to be fuzzed
  MmsValue_printToBuffer(value, buffer.data(), buffer.size());

  // Clean up
  MmsValue_delete(value);

  return 0;
}