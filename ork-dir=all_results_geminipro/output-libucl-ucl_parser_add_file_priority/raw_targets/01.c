#include "ucl.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  FuzzedDataProvider provider(data, size);
  std::string filename = provider.ConsumeRemainingBytesAsString();
  int priority = provider.ConsumeIntegral<int>();

  if (ucl_parser_add_file_priority(parser, (char *)filename.c_str(), priority)) {
    return 0;
  }

  ucl_parser_free(parser);
  return 0;
}