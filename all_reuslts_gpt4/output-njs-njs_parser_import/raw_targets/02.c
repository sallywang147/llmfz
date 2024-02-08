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
  FuzzedDataProvider stream(data, size);

  // Initialize the parser
  njs_parser_s parser;
  njs_parser_start(&parser);

  // Initialize the lexer token
  njs_lexer_token_t token;
  token.start = stream.ConsumeBytesAsString(stream.remaining_bytes()).c_str();
  token.end = token.start + strlen(token.start);

  // Initialize the queue link
  njs_queue_link_s current;
  njs_queue_init(&current);

  // Call the target function
  njs_parser_import(&parser, &token, &current);

  return 0;
}