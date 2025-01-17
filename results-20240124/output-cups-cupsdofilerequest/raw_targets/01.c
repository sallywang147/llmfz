 #include "cups.h"
#include "ipp.h"
#include "http.h"
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t resource_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto resource = provider.ConsumeBytes<char>(resource_size);
  const size_t filename_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto filename = provider.ConsumeBytes<char>(filename_size);

  cupsDoFileRequest(nullptr, nullptr, resource.data(), filename.data());

  return 0;
}