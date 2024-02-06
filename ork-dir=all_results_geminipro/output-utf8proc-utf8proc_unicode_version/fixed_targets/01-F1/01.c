#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "utf8proc.h"

extern "C" {
#include "utf8proc.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    utf8proc_init();
    initialized = true;
  }

  std::vector<uint8_t> input_buffer(data, data + size);
  utf8proc_unicode_version();

  return 0;
}