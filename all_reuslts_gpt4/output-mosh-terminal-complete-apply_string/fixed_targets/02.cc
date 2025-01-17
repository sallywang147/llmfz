#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

#include "src/statesync/completeterminal.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Terminal::Complete complete(80, 24);
  FuzzedDataProvider provider(data, size);
  std::string diff = provider.ConsumeRemainingBytesAsString();
  complete.apply_string(diff);
  return 0;
}