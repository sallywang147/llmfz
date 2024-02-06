#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "ucl.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t chunk_size = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  std::vector<uint8_t> chunk_data(chunk_size);
  provider.ConsumeBytes<uint8_t>(chunk_data.data(), chunk_size);
  struct ucl_chunk chunk = {chunk_data.data(), chunk_size};

  struct ucl_parser* parser = ucl_parser_new(0);
  struct ucl_object* obj = ucl_parse_macro_arguments(parser, &chunk);
  if (obj) {
    ucl_object_unref(obj);
  }
  ucl_parser_free(parser);

  return 0;
}