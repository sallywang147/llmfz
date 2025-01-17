#include <fuzzer/FuzzedDataProvider.h>
#include "ck_hash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  float key = stream.ConsumeFloatingPoint<float>();
  std::string value = stream.ConsumeRemainingBytesAsString();

  struct ck_hash_table_s table;
  ck_hash_table_init(&table, 10); // Initialize the table with a small size

  ck_float_hash_insert(key, (char*)value.c_str(), &table);

  ck_hash_table_destroy(&table);

  return 0;
}