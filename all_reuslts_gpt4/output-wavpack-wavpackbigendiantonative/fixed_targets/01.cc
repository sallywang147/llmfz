#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "wavpack/wavpack.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Consume a string for the "format" parameter.
  std::string format = stream.ConsumeBytesAsString(1);
  
  // Consume the remaining bytes for the "data" parameter.
  std::string data_str = stream.ConsumeRemainingBytesAsString();

  // Call the function under test.
  WavpackBigEndianToNative(&data_str[0], &format[0]);

  return 0;
}