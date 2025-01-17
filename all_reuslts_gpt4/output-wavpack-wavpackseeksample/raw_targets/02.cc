#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "wavpack.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int32_t sample = stream.ConsumeIntegral<int32_t>();

  // Create WavpackContext
  char error[80];
  WavpackContext *wpc = WavpackOpenFileInput((char*)data, error, OPEN_STREAMING, 0);
  if (!wpc) return 0;

  // Call the target function
  WavpackSeekSample(wpc, sample);

  // Cleanup
  WavpackCloseFile(wpc);

  return 0;
}