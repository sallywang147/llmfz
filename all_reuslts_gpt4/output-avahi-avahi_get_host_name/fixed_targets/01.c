#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/strlst.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data from the input stream to use as parameters for avahi_get_host_name.
  size_t bufferSize = stream.ConsumeIntegralInRange<size_t>(0, 256);
  std::vector<char> buffer(bufferSize, 0);

  avahi_get_host_name(buffer.data(), bufferSize);

  return 0;
}