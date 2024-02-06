#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "pg_query.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = str.c_str();

  char *json = pg_query_node_to_json(ptr);

  if (json != NULL) {
    free(json);
  }

  return 0;
}