#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "parallel_hashmap/phmap_dump.h"
#include "parallel_hashmap/phmap_generated.h"
#include "parallel_hashmap/phmap_hash_base.h"
#include "parallel_hashmap/phmap_hash_container.h"
#include "parallel_hashmap/phmap_hash_policy.h"
#include "parallel_hashmap/phmap_hash_set.h"
#include "parallel_hashmap/phmap_hash_table.h"
#include "parallel_hashmap/phmap_hash_vector.h"
#include "parallel_hashmap/phmap_node_hash_policy.h"
#include "parallel_hashmap/phmap_parallel.h"
#include "parallel_hashmap/phmap_type_hash.h"
#include "parallel_hashmap/phmap_unordered_set.h"
#include "parallel_hashmap/phmap_unordered_set_node_hash_policy.h"
#include "parallel_hashmap/phmap_unordered_set_type_hash.h"
#include "parallel_hashmap/phmap_unordered_vector.h"
#include "parallel_hashmap/phmap_unordered_vector_node_hash_policy.h"
#include "parallel_hashmap/phmap_unordered_vector_type_hash.h"
#include "parallel_hashmap/phmap_vector.h"
#include <fuzzer/FuzzedDataProvider.h>

using std::string;
using phmap::flat_hash_map;

void test_assignments(const uint8_t *data, size_t size) {
  phmap::flat_hash_map<std::string, std::string> email;
  FuzzedDataProvider fuzzed_data(data, size);
  const int num_items = fuzzed_data.ConsumeIntegral<int16_t>();
  for (int i = 0; i < num_items; ++i) {
    email.insert(phmap::flat_hash_map<std::string, std::string>::value_type(fuzzed_data.ConsumeRandomLengthString(), fuzzed_data.ConsumeRandomLengthString()));
  }
  // Iterate through all of the items.
  for (const auto &n : email) {
    (void)n;
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  test_assignments(data, size);
  return 0;
}