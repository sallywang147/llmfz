#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    initialized = true;
  }
  // Initially, start by feeding the decoder more data.
  int decode_ret = 0;
  FuzzedDataProvider provider(data, size);
  while ((decode_ret != -1)) {
    if (decode_ret == 0) {
      if (provider.remaining_bytes() == 0) {
        break;
      }
      const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
          0,
          provider.remaining_bytes());
      auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
      decode_ret = main_loop();
    } else {
      // Unhandled mpg123_decode return value.
      abort();
    }
  }

  return 0;
}