#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "meshoptimizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  const size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(1, size);
  std::vector<char> buffer(buffer_size);

  std::string data_str = stream.ConsumeRemainingBytesAsString();
  char* data_end = const_cast<char*>(data_str.data() + data_str.size());

  meshopt::decodeBytes(const_cast<char*>(data_str.data()), data_end, buffer.data(), buffer_size);

  return 0;
}