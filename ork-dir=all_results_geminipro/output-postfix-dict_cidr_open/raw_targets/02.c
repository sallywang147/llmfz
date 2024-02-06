#include <fuzzer/FuzzedDataProvider.h>

#include <stdlib.h>
#include <string.h>

#include "dict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Generate a random string for the dictionary name.
  size_t name_length = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  char *name = (char *)malloc(name_length + 1);
  provider.ConsumeBytes(name, name_length);
  name[name_length] = '\0';

  // Generate random values for the other arguments.
  int flags = provider.ConsumeIntegral<int>();
  int mode = provider.ConsumeIntegral<int>();

  // Call the function under test.
  struct DICT *dict = dict_cidr_open(name, flags, mode);

  // Clean up.
  free(name);
  if (dict != NULL) {
    dict_free(dict);
  }

  return 0;
}