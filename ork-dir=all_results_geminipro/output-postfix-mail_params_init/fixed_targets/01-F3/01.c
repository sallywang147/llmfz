#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mail_params.h"

extern "C" {
#include "mail_params.c"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    mail_params_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  // mail_params_init() only takes a single argument, so we'll just
  // provide it with a random integer.
  int arg = provider.ConsumeIntegral<int>();

  mail_params_init(arg);

  return 0;
}