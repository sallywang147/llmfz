#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int fd = provider.ConsumeIntegral<int>();
  short what = provider.ConsumeIntegral<short>();
  std::string arg = provider.ConsumeRemainingBytesAsString();

  levent_update_and_send(fd, what, const_cast<char*>(arg.c_str()));

  return 0;
}