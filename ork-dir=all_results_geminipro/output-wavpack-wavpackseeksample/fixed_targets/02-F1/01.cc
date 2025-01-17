#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "wavpack.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int sample = stream.ConsumeIntegral<int>();
  struct WavpackContext* wpc = WavpackOpenFileInputEx(nullptr, nullptr, 0, 0);
  if (wpc == nullptr) {
    return 0;
  }
  int ret = WavpackSeekSample(wpc, sample);
  WavpackCloseFile(wpc);
  return ret;
}