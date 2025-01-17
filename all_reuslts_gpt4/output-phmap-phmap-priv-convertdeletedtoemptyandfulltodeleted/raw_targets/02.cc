#include <fuzzer/FuzzedDataProvider.h>
#include "phmap.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract an array of bytes as a vector.
  std::vector<char> ctrl = stream.ConsumeBytes<char>(stream.remaining_bytes());

  // Call the function with the fuzzed inputs
  phmap::priv::ConvertDeletedToEmptyAndFullToDeleted(ctrl.data(), ctrl.size());

  return 0;
}