#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "njs_parser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct njs_parser_s parser = {0};
  struct njs_lexer_token_t token = {0};
  struct njs_queue_link_s current = {0};
  const std::string text = stream.ConsumeRemainingBytesAsString();

  njs_parser_call_expression(&parser, &token, &current);
  return 0;
}