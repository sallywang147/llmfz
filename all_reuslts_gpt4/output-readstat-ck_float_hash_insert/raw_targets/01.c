#include <fuzzer/FuzzedDataProvider.h>
#include "ck_hash_table.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize hash table
  struct ck_hash_table_s *table = ck_hash_table_init(10);

  // Get a float key from the fuzzer
  float key = stream.ConsumeFloatingPoint<float>();

  // Get a string value from the fuzzer
  std::string strValue = stream.ConsumeRemainingBytesAsString();
  char *value = const_cast<char *>(strValue.c_str());

  // Call the function to be fuzzed
  ck_float_hash_insert(key, value, table);

  // Clean up
  ck_hash_table_free(table);

  return 0;
}