#include <fuzzer/FuzzedDataProvider.h>

#include <stdint.h>
#include <stdlib.h>

#include "dict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Generate random values for the function arguments.
  size_t arg0_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  char *arg0 = (char *)malloc(arg0_size + 1);
  provider.ConsumeBytes(arg0, arg0_size);
  arg0[arg0_size] = '\0';
  int arg1 = provider.ConsumeIntegral<int>();
  int arg2 = provider.ConsumeIntegral<int>();

  // Call the function with the generated arguments.
  struct DICT *result = dict_cidr_open(arg0, arg1, arg2);

  // Free the allocated memory.
  free(arg0);

  // Use the result to prevent unused variable warning.
  (void)result;

  return 0;
}