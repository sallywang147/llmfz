#include "ucl.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  std::string filename = stream.ConsumeRandomLengthString();
  int priority = stream.ConsumeIntegral<int>();

  ucl_parser_add_file_priority(parser, (char *)filename.c_str(), priority);

  ucl_parser_free(parser);
  return 0;
}