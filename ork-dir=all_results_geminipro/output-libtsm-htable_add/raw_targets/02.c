#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "shl_htable.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct shl_htable_int* table = shl_htable_int_new(1024);
  std::vector<char*> keys;

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    size_t hash = provider.ConsumeIntegral<size_t>();
    size_t key_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
    std::string key = provider.ConsumeRandomLengthString(key_size);
    char* key_ptr = key.data();
    keys.push_back(key_ptr);
    bool ret = htable_add(table, hash, key_ptr);
    if (!ret) {
      abort();
    }
  }

  for (auto key : keys) {
    shl_htable_int_remove(table, shl_htable_int_hash(key), key);
  }

  shl_htable_int_free(table);
  return 0;
}