#include "ucl.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);
  std::string filename = stream.ConsumeRandomLengthString();
  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  ucl_parser_add_file(parser, const_cast<char *>(filename.c_str()));

  ucl_parser_free(parser);
  return 0;
}