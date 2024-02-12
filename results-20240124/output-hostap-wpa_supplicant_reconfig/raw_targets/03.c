 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wpa_supplicant/wpa_supplicant.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  int sig = provider.ConsumeIntegral<int>();
  char *signal_ctx = provider.ConsumeBytesAsString(provider.remaining_bytes()).data();

  wpa_supplicant_reconfig(sig, signal_ctx);

  return 0;
}