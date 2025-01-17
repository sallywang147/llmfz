#include <fuzzer/FuzzedDataProvider.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" char * run_thread_poll_loop(char * data);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  size_t data_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  char *data_ptr = provider.ConsumeBytes<char>(data_size);

  char *result = run_thread_poll_loop(data_ptr);
  free(result);

  return 0;
}