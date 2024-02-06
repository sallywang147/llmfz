#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "speex/speex.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  const size_t state_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  char* state = new char[state_size];
  provider.ConsumeBytes(state, state_size);

  const size_t vin_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  char* vin = new char[vin_size];
  provider.ConsumeBytes(vin, vin_size);

  SpeexBits bits;
  speex_bits_init(&bits);
  int ret = sb_encode(state, vin, &bits);
  speex_bits_destroy(&bits);

  delete[] state;
  delete[] vin;
  return ret;
}
```

The issue was that the header file `speex.h` was not wrapped with `extern "C" {}`, which is necessary for C++ to properly link to C functions.