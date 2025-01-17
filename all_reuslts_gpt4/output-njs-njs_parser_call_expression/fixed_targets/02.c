#include <fuzzer/FuzzedDataProvider.h>
#include "njs_parser.h"
#include "njs_lexer.h"
#include "njs_queue.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize parser
  njs_parser_t parser;
  njs_parser_init(&parser);

  // Initialize lexer token
  njs_lexer_token_t token;
  njs_lexer_token_init(&token);

  // Initialize queue link
  njs_queue_link_t current;
  njs_queue_link_init(&current);

  // Call the target function
  njs_parser_call_expression(&parser, &token, &current);

  return 0;
}