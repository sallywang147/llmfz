#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "aacenc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct AACENCODER hAacEncoder;
  struct USER_PARAM config;

  FuzzedDataProvider provider(data, size);

  int InitFlags = provider.ConsumeIntegral<int>();

  // Initialize the USER_PARAM struct with fuzzed data.
  config.bitRate = provider.ConsumeIntegral<uint32_t>();
  config.sampleRate = provider.ConsumeIntegral<uint32_t>();
  config.channels = provider.ConsumeIntegral<uint32_t>();
  config.bandWidth = provider.ConsumeIntegral<uint32_t>();

  // Call the function under test.
  aacEncInit(&hAacEncoder, InitFlags, &config);

  return 0;
}