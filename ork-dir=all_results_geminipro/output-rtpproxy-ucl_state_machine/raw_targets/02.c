#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ucl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    ucl_init();
    initialized = true;
  }

  ucl_parser *parser = ucl_parser_new(0);
  if (parser == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
        0, provider.remaining_bytes());
    auto next_input = provider.ConsumeBytes<char>(next_size);
    if (!ucl_parser_add(parser, next_input.data(), next_input.size())) {
      break;
    }
    ucl_state_machine(parser);
  }

  ucl_parser_free(parser);

  return 0;
}