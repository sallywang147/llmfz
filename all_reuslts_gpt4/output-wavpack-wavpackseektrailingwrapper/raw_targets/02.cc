#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wavpack/wavpack.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char error[80];
  WavpackContext *wpc = WavpackOpenFileInput(
      reinterpret_cast<char *>(const_cast<uint8_t *>(data)), error, OPEN_WVC, 0);

  if (!wpc) {
    return 0;
  }

  WavpackSeekTrailingWrapper(wpc);
  WavpackCloseFile(wpc);

  return 0;
}