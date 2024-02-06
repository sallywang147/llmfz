#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ck_hash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ck_hash_table_s table;
  if (ck_hash_table_init(&table, 100) != 0) {
    return 0;
  }

  while (stream.remaining_bytes() > 0) {
    double key = stream.ConsumeFloatingPoint<double>();
    std::string value = stream.ConsumeRandomLengthString();
    ck_double_hash_insert(key, (char*)value.c_str(), &table);
  }

  ck_hash_table_destroy(&table);

  return 0;
}