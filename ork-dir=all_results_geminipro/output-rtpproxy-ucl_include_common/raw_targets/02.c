#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ucl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    ucl_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  std::vector<uint8_t> buffer(provider.ConsumeRemainingBytes());

  ucl_parser* parser = ucl_parser_new(0);
  if (parser == nullptr) {
    return 0;
  }

  bool default_try = provider.ConsumeBool();
  bool default_sign = provider.ConsumeBool();

  ucl_object_s* args = ucl_object_new(parser);
  if (args == nullptr) {
    ucl_parser_free(parser);
    return 0;
  }

  bool success = ucl_include_common(reinterpret_cast<char*>(buffer.data()),
                                    buffer.size(), args, parser, default_try,
                                    default_sign);
  if (!success) {
    ucl_object_free(args);
    ucl_parser_free(parser);
    return 0;
  }

  ucl_object_free(args);
  ucl_parser_free(parser);

  return 0;
}