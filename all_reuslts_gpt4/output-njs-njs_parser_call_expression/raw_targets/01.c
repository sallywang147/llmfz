#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "njs_parser.h"
#include "njs_lexer.h"
#include "njs_queue.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 3) {
    // Not enough data for any meaningful fuzzing.
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Initialize parser
  njs_parser_s parser;
  njs_parser_init(&parser);

  // Initialize lexer token
  njs_lexer_token_t token;
  njs_lexer_token_init(&token);

  // Initialize queue link
  njs_queue_link_s current;
  njs_queue_link_init(&current);

  // Call the target function
  njs_parser_call_expression(&parser, &token, &current);

  return 0;
}