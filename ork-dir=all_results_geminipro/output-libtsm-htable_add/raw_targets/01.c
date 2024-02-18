#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "libhtable.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct shl_htable_int *ht = shl_htable_int_new();
  if (!ht)
    return 0;

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    size_t hash = provider.ConsumeIntegral<size_t>();
    std::string str = provider.ConsumeRandomLengthString();
    char *p = str.c_str();
    htable_add(ht, hash, p);
  }

  shl_htable_int_free(ht);
  return 0;
}