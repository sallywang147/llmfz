#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "wavpack.h"

extern "C" {
#include "wavpack/wavpack.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  WavpackContext* wpc = WavpackOpenFileInput(nullptr, nullptr, 0, nullptr);
  if (wpc == nullptr) {
    return 0;
  }
  WavpackSeekTrailingWrapper(wpc);
  WavpackCloseFile(wpc);
  return 0;
}