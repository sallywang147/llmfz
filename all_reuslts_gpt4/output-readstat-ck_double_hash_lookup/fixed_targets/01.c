#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "ck_hash_table.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(double)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize hash table
  struct ck_hash_table_s table;
  ck_hash_table_init(&table);

  // Consume a double from the data stream
  double key = stream.ConsumeFloatingPoint<double>();

  // Call the function to fuzz
  char* result = ck_double_hash_lookup(key, &table);

  // Cleanup
  ck_hash_table_free(&table);

  return 0;
}