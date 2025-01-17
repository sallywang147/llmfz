#include <fuzzer/FuzzedDataProvider.h>
#include <sdb.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include <sdb.h>
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  char *name = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 1024)).c_str();
  char *user = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 1024)).c_str();
  char *password = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 1024)).c_str();
  int flags = provider.ConsumeIntegral<int>();
  int mode = provider.ConsumeIntegral<int>();
  int fd = provider.ConsumeIntegral<int>();
  struct SDBStr_2311 **sdbs = nullptr;
  struct SDBStr_2311 **sdbs2 = nullptr;
  int *fd2 = nullptr;
  size_t ret = sdb_open(name, user, password, flags, mode, fd, &sdbs, &sdbs2, fd2);
  sdb_close(sdbs);
  free(name);
  free(user);
  free(password);
  return ret;
}

extern "C" size_t sdb_open(char *name, char *user, char *password, int flags, int mode, int fd, struct SDBStr_2311 **sdbs, struct SDBStr_2311 **sdbs2, int *fd2) {
  return 0;
}