#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  int fd = provider.ConsumeIntegral<int>();
  char* name = provider.ConsumeRandomLengthString().c_str();
  int flags = provider.ConsumeIntegral<int>();
  struct __dirstream **ret = nullptr;

  int result = opendirat(fd, name, flags, ret);

  if (result == 0) {
    closedir(*ret);
  }

  return 0;
}