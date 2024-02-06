#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "njs_parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  njs_parser_s parser;
  njs_lexer_token_t token;
  njs_queue_link_s current;

  // Initialize parser, token and current with fuzzed data
  if (provider.remaining_bytes() < sizeof(parser) + sizeof(token) + sizeof(current)) {
    return 0;
  }

  provider.ConsumeData(&parser, sizeof(parser));
  provider.ConsumeData(&token, sizeof(token));
  provider.ConsumeData(&current, sizeof(current));

  njs_parser_import(&parser, &token, &current);

  return 0;
}