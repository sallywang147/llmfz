#include "http_parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  http_parser parser;
  http_parser_init(&parser, HTTP_BOTH);

  int pause = provider.ConsumeIntegral<int>();
  http_parser_pause(&parser, pause);

  return 0;
}