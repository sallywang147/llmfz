#include <fuzzer/FuzzedDataProvider.h>

#include "hal_thread.h"
#include "iec61850_server.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a MmsValue object with a random type.
  MmsValue* value = MmsValue_createEmptyArray(stream.ConsumeIntegral<int>());
  if (value == NULL) {
    return 0;
  }

  // Allocate a buffer for the encoded result.
  char buffer[4096];

  // Get a random position in the buffer.
  int bufPos = stream.ConsumeIntegralInRange<int>(0, sizeof(buffer) - 1);

  // Get a random boolean value.
  bool encode = stream.ConsumeBool();

  // Call the function to fuzz.
  encodeArrayAccessResult(value, buffer, bufPos, encode);

  // Clean up.
  MmsValue_delete(value);

  return 0;
}