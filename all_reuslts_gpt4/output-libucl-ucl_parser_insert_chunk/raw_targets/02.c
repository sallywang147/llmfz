#include "ucl.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  std::string chunk = stream.ConsumeRandomLengthString();
  bool result = ucl_parser_insert_chunk(parser, const_cast<char *>(chunk.c_str()), chunk.size());

  ucl_parser_free(parser);
  return 0;
}