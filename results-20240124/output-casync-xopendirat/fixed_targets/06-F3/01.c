#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int fd = stream.ConsumeIntegral<int>();
  const std::string name = stream.ConsumeRemainingBytesAsString();
  const int flags = stream.ConsumeIntegral<int>();
  struct __dirstream* ret;

  int xopendirat_ret = xopendirat(fd, const_cast<char*>(name.c_str()), flags, &ret);
  if (xopendirat_ret == -1) {
    return 0;
  }

  closedir(ret);
  return 0;
}