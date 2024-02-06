#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "parallel_hashmap/phmap_dump.h"
#include <fuzzer/FuzzedDataProvider.h>

using phmap::flat_hash_set;
using namespace std;

extern "C" {
#include "parallel_hashmap/phmap.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  phmap::flat_hash_set<unsigned int> table;
  FuzzedDataProvider provider(data, size);
  const int num_items = provider.ConsumeIntegral<int16_t>();

  for (int i = 0; i < num_items; ++i) {
    table.insert(provider.ConsumeIntegral<uint32_t>());
  }

  size_t pos = provider.ConsumeIntegralInRange<size_t>(0, table.size());
  phmap::drop_deletes_without_resize(&table, pos);

  return 0;
}