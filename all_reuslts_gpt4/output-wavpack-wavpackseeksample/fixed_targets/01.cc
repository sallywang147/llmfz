#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wavpack/wavpack.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize WavpackContext
  char error[80];
  WavpackContext *wpc = WavpackOpenFileInput((char *)data, error, OPEN_TAGS, 0);
  if (!wpc) {
    return 0;
  }

  // Consume integer for sample
  int sample = stream.ConsumeIntegral<int>();

  // Call the target function
  WavpackSeekSample(wpc, sample);

  // Cleanup
  WavpackCloseFile(wpc);

  return 0;
}