#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "wavpack.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  WavpackContext* wpc = WavpackOpenFileInput(nullptr, nullptr, 0, 0, 0);
  if (wpc == nullptr) {
    return 0;
  }

  const int sample = stream.ConsumeIntegral<int>();
  WavpackSeekSample(wpc, sample);

  WavpackCloseFile(wpc);
  return 0;
}