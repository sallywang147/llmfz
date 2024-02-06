#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <dirent.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  int fd = provider.ConsumeIntegral<int>();
  size_t name_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> name_bytes = provider.ConsumeBytes<uint8_t>(name_size);
  char* name = reinterpret_cast<char*>(name_bytes.data());
  int flags = provider.ConsumeIntegral<int>();
  DIR** ret = nullptr;

  int result = opendirat(fd, name, flags, ret);

  if (result == 0) {
    closedir(*ret);
  }

  return 0;
}