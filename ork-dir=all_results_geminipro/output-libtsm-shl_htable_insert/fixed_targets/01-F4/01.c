#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "shl_htable.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    shl_htable_init();
    initialized = true;
  }
  shl_htable_t* htable = shl_htable_new();
  if (htable == nullptr) {
    return 0;
  }

  // Create a vector of bytes to hold the object to be inserted into the hash table.
  std::vector<uint8_t> object(size);
  // Copy the data from the input buffer into the object vector.
  std::copy(data, data + size, object.begin());

  // Generate a hash value for the object using the provided data.
  size_t hash = 0;
  for (size_t i = 0; i < size; i++) {
    hash += data[i];
  }

  // Insert the object into the hash table using the generated hash value.
  int ret = shl_htable_insert(htable, (const char *)object.data(), hash);

  // Free the hash table.
  shl_htable_free(htable);

  return ret;
}