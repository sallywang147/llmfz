#include <fuzzer/FuzzedDataProvider.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

extern "C" {
#include <algorithm>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int fd = stream.ConsumeIntegral<int>();
  int flags = stream.ConsumeIntegral<int>();
  char *name = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 128)).c_str();
  struct __dirstream *ret;

  int res = xopendirat(fd, name, flags, &ret);
  if (res == 0) {
    closedir(ret);
  }
  return 0;
}