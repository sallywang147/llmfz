#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "ck_hash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const double key = stream.ConsumeFloatingPoint<double>();
  const size_t table_size = stream.ConsumeIntegralInRange<size_t>(1, 10000);
  ck_hash_table_t* table = ck_hash_init(table_size);
  if (table == nullptr) {
    return 0;
  }
  char* value = ck_double_hash_lookup(key, table);
  if (value != nullptr) {
    ck_free(value);
  }
  ck_hash_destroy(table);
  return 0;
}