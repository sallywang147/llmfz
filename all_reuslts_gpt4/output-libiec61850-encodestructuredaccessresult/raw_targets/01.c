#include <fuzzer/FuzzedDataProvider.h>
#include "libiec61850/mms_value.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a MmsValue object
  MmsValue* value = MmsValue_newIntegerFromInt32(stream.ConsumeIntegral<int32_t>());

  // Create a buffer to hold the encoded result
  std::vector<char> buffer(size);
  int bufPos = stream.ConsumeIntegralInRange<int>(0, size - 1);

  // Determine whether to encode or not
  bool encode = stream.ConsumeBool();

  // Call the function under test
  encodeStructuredAccessResult(value, buffer.data(), bufPos, encode);

  // Clean up
  MmsValue_delete(value);

  return 0;
}