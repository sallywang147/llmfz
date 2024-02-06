#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pg_query.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRemainingBytesAsString();
  char* ptr = const_cast<char*>(str.c_str());

  pg_query_nodes_to_protobuf(ptr);

  return 0;
}