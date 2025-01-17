#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lzo2a_999_swd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(struct lzo2a_999_swd_t)) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  struct lzo2a_999_swd_t swd;
  size_t consumed = provider.ConsumeData(&swd, sizeof(swd));
  if (consumed != sizeof(swd)) {
    return 0;
  }

  size_t node = provider.ConsumeIntegral<size_t>();
  size_t len = provider.ConsumeIntegral<size_t>();

  swd_insertdict(&swd, node, len);

  return 0;
}