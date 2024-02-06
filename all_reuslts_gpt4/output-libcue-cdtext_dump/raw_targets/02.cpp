#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "cdtext.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct Cdtext* cdtext = cdtext_init();
  if (cdtext == nullptr) {
    return 0;
  }

  int arg = stream.ConsumeIntegral<int>();

  cdtext_dump(cdtext, arg);

  cdtext_destroy(cdtext);

  return 0;
}