#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "shl_htable.h"

extern "C" {
#include "fuzzer_support.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct shl_htable *htable = shl_htable_new(1024, 0.75);
  if (htable == NULL) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    size_t hash = provider.ConsumeIntegral<size_t>();
    size_t obj_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
    std::vector<char> obj(obj_size);
    provider.ConsumeBytes<char>(obj.data(), obj_size);
    shl_htable_insert(htable, obj.data(), obj_size, hash, obj_size); // Fix: Pass obj_size as the fourth argument
  }

  shl_htable_free(htable);

  return 0;
}