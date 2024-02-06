#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "wavpack.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // We need at least one byte for the format string
  if (provider.remaining_bytes() < 1) {
    return 0;
  }

  // Consume a string for the format
  std::string format = provider.ConsumeBytesAsString(1);
  // Consume the remaining bytes for the data
  std::string wavData = provider.ConsumeRemainingBytesAsString();

  // Call the target function
  WavpackNativeToBigEndian(const_cast<char*>(wavData.data()), const_cast<char*>(format.data()));

  return 0;
}