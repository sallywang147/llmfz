#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "iec61850_server.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need to create a MmsValue to pass to the function.
  MmsValue* value = MmsValue_newEmptyStructure(1);
  if (value == NULL) {
    return 0;
  }

  // Create a buffer to hold the result of the encoding.
  std::vector<char> buffer(stream.ConsumeIntegralInRange<size_t>(0, size));

  // Get a position within the buffer.
  int bufPos = stream.ConsumeIntegralInRange<int>(0, buffer.size() - 1);

  // Get a boolean value to determine if we should encode or not.
  bool encode = stream.ConsumeBool();

  // Call the function under test.
  encodeArrayAccessResult(value, buffer.data(), bufPos, encode);

  // Clean up.
  MmsValue_delete(value);

  return 0;
}