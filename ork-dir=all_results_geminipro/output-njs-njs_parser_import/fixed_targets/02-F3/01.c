#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "njs_parser.h"

extern "C" {
#include "njs_parser_types.h"
#include "njs_parser_api.h"
}

void njs_parser_init(njs_parser_s* parser) {
  memset(parser, 0, sizeof(njs_parser_s));
}

int njs_parser_get_token(njs_parser_s* parser, njs_lexer_token_t* token) {
  return njs_lexer_get_token(parser->lexer, token);
}

int njs_parser_import(njs_parser_s* parser, njs_lexer_token_t* token, njs_queue_link_s* current) {
  return njs_parser_parse_import(parser, token, current);
}

void njs_parser_free(njs_parser_s* parser) {
  njs_lexer_free(parser->lexer);
  free(parser);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  njs_parser_s parser;
  njs_parser_init(&parser);
  njs_lexer_token_t token;
  njs_queue_link_s current;

  const std::string source = stream.ConsumeRemainingBytesAsString();
  const char* source_ptr = source.c_str();
  const size_t source_len = source.size();
  njs_parser_set_source(&parser, source_ptr, source_len);

  while (njs_parser_get_token(&parser, &token) == NJS_OK) {
    njs_parser_import(&parser, &token, &current);
  }

  njs_parser_free(&parser);
  return 0;
}