#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "ole2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  char *filename_c_str = strdup(filename.c_str());
  struct OLE2 *ole2 = ole2_open_file(filename_c_str);
  if (ole2) {
    ole2_close(ole2);
  }
  free(filename_c_str);
  return 0;
}