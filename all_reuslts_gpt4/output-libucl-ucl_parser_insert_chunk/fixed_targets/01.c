#include "ucl.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Create a parser
  struct ucl_parser *parser = ucl_parser_new(0);

  // Use FuzzedDataProvider to generate inputs
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = const_cast<char*>(str.c_str());

  // Call the function
  bool result = ucl_parser_insert_chunk(parser, ptr, str.size());

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}