#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "brunsli/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize parameters for FindBestMatrix function
  int int_arg = stream.ConsumeIntegral<int>();
  bool bool_arg = stream.ConsumeBool();

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<char> bytes = stream.ConsumeRemainingBytes<char>();
  char *char_ptr = bytes.data();

  // Call the function to fuzz
  brunsli::FindBestMatrix(&int_arg, bool_arg, char_ptr);

  return 0;
}