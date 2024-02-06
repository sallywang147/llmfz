#include "http_parser.h"
#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  http_parser parser;
  http_parser_init(&parser, HTTP_BOTH);

  FuzzedDataProvider stream(data, size);
  int pause = stream.ConsumeIntegral<int>();

  http_parser_pause(&parser, pause);

  return 0;
}