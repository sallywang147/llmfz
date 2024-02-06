#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libraw/libraw.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string filename = stream.ConsumeRandomLengthString();
  
  LibRaw RawProcessor;
  int ret = RawProcessor.open_file(filename.c_str());
  
  if (ret != LIBRAW_SUCCESS) {
    // handle error
    return 0;
  }

  // process the file
  ret = RawProcessor.unpack();
  if (ret != LIBRAW_SUCCESS) {
    // handle error
    return 0;
  }

  RawProcessor.recycle(); // Recycle the processor

  return 0;
}