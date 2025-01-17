#include <fuzzer/FuzzedDataProvider.h>
#include <stdlib.h>
#include <ucl.h>

extern "C" {
#include <ucl/ucl.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct ucl_parser *parser = ucl_parser_new(0);
  if (!parser) {
    return 0;
  }
  struct ucl_chunk chunk;
  chunk.len = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  chunk.data = provider.ConsumeBytes<char>(chunk.len);
  struct ucl_object_s *object = ucl_parse_macro_arguments(parser, &chunk);
  ucl_object_unref(object);
  ucl_parser_free(parser);
  return 0;
}