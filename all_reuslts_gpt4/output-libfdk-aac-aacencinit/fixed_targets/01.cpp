#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "aacenc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct AACENCODER hAacEncoder;
  int InitFlags = stream.ConsumeIntegral<int>();
  struct USER_PARAM config;

  size_t consumed = stream.ConsumeData(&config, sizeof(config));

  if (consumed != sizeof(config)) {
    return 0;
  }

  aacEncInit(&hAacEncoder, InitFlags, &config);

  return 0;
}