#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ck_hash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the hash table
  struct ck_hash_table_s *table = ck_hash_table_init(10);

  // Consume data from the stream to create keys and values for the hash table
  while (stream.remaining_bytes() > 0) {
    double key = stream.ConsumeFloatingPoint<double>();
    char *value = strdup(stream.ConsumeRandomLengthString().c_str());

    // Insert the key-value pair into the hash table
    ck_hash_table_insert(table, key, value);
  }

  // Now use the same data to lookup keys in the hash table
  FuzzedDataProvider lookupStream(data, size);
  while (lookupStream.remaining_bytes() > 0) {
    double key = lookupStream.ConsumeFloatingPoint<double>();

    // Perform the lookup
    char *value = ck_double_hash_lookup(key, table);
  }

  // Cleanup
  ck_hash_table_free(table);

  return 0;
}