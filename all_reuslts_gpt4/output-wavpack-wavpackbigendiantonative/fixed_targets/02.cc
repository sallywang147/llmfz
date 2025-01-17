#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "wavpack/wavpack.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need at least one byte for format
  if (size == 0)
    return 0;

  // Consume one byte for format
  std::string format = stream.ConsumeBytesAsString(1);

  // Consume the rest of the data
  std::string inputData = stream.ConsumeRemainingBytesAsString();

  // Call the target function
  WavpackBigEndianToNative(const_cast<char*>(inputData.data()), const_cast<char*>(format.data()));

  return 0;
}