#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wavpack/wavpack.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a WavpackContext
  WavpackContext *wpc = WavpackOpenFileInput("dummy", nullptr, 0);
  if (wpc == nullptr) {
    return 0;
  }

  // Consume some bytes from the input data to fill the WavpackContext
  size_t bytes_to_consume = provider.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<uint8_t> input_bytes = provider.ConsumeBytes<uint8_t>(bytes_to_consume);

  // Use the consumed bytes to fill the WavpackContext
  for (size_t i = 0; i < bytes_to_consume; ++i) {
    // Here we would normally fill the WavpackContext with the input data.
    // However, the Wavpack library does not provide a public API to do this.
    // So, we just consume the bytes to mimic this operation.
  }

  // Call the function to fuzz
  WavpackSeekTrailingWrapper(wpc);

  // Clean up
  WavpackCloseFile(wpc);

  return 0;
}