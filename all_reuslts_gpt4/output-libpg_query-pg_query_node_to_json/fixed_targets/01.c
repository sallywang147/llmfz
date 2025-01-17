#include <fuzzer/FuzzedDataProvider.h>
#include <pg_query.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string from the input data
  std::string str = stream.ConsumeBytesAsString(stream.remaining_bytes());
  char *ptr = const_cast<char*>(str.c_str());

  // Call the target function
  char* json = pg_query_node_to_json(ptr);

  // Free the memory allocated by pg_query_node_to_json
  if (json != nullptr) {
    free(json);
  }

  return 0;
}