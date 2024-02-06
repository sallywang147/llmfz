#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>

#include "dict.h"

extern "C" {
#include "dict_regexp.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Generate a random string for the dictionary file name.
  const size_t filename_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> filename(filename_size);
  provider.ConsumeBytes(filename.data(), filename_size);

  // Generate random values for the other arguments.
  const int flags = provider.ConsumeIntegral<int>();
  const int mode = provider.ConsumeIntegral<int>();

  // Call the function under test.
  struct DICT* dict = dict_regexp_open(filename.data(), flags, mode);

  // Clean up.
  if (dict != nullptr) {
    dict_free(dict);
  }

  return 0;
}