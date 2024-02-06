#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "../ini.h"
}

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  const size_t max_str_len = provider.ConsumeIntegralInRange<size_t>(5, 100);
  char *str = (char *)malloc(max_str_len + 1);
  provider.ConsumeBytes(str, max_str_len);
  str[max_str_len] = '\0';

  const size_t max_num = provider.ConsumeIntegralInRange<size_t>(0, 100);
  char num_str[100];
  sprintf(num_str, "%zu", max_num);

  const size_t max_stream_len = provider.ConsumeIntegralInRange<size_t>(5, 100);
  char *stream = (char *)malloc(max_stream_len + 1);
  provider.ConsumeBytes(stream, max_stream_len);
  stream[max_stream_len] = '\0';

  char *result = ini_reader_string(str, max_num, stream);
  if (result) {
    free(result);
  }

  free(str);
  free(stream);

  return 0;
}