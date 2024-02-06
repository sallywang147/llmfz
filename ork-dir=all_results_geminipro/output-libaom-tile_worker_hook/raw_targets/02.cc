#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t len1 = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  size_t len2 = provider.ConsumeIntegralInRange<size_t>(0, 1000);

  std::vector<uint8_t> buf1(len1);
  std::vector<uint8_t> buf2(len2);
  provider.ConsumeBytes<uint8_t>(buf1.data(), len1);
  provider.ConsumeBytes<uint8_t>(buf2.data(), len2);

  tile_worker_hook((char*)buf1.data(), (char*)buf2.data());

  return 0;
}