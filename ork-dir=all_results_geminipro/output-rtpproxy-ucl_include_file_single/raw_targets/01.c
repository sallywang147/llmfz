#include <fuzzer/FuzzedDataProvider.h>
#include <stdlib.h>
#include <string.h>
#include <ucl/ucl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t len = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  char *data_copy = (char *)malloc(len + 1);
  provider.ConsumeBytes(data_copy, len);
  data_copy[len] = '\0';

  struct ucl_parser *parser = ucl_parser_new(0);
  struct ucl_include_params params = {0};

  bool result = ucl_include_file_single(data_copy, len, parser, &params);

  free(data_copy);
  ucl_parser_free(parser);

  return 0;
}