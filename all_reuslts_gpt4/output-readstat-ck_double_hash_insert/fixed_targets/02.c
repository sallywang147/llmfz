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

  FuzzedDataProvider provider(data, size);
  double key = provider.ConsumeFloatingPoint<double>();
  std::string value = provider.ConsumeRemainingBytesAsString();
  
  struct ck_hash_table_s table;
  ck_hash_table_init(&table, 10); // Initialize hash table with size 10

  ck_double_hash_insert(key, const_cast<char*>(value.c_str()), &table);

  ck_hash_table_destroy(&table); // Clean up the table

  return 0;
}