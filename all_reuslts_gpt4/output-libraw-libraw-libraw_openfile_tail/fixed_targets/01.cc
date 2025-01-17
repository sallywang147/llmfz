#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libraw/libraw.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  LibRaw *libraw = new LibRaw();

  if (libraw == nullptr) {
    return 0;
  }

  try {
    libraw->libraw_openfile_tail(libraw, &stream);
  } catch (std::exception &e) {
    delete libraw;
    return 0;
  }

  delete libraw;

  return 0;
}