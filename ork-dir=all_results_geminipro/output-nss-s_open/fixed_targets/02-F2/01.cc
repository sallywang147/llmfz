#include <fuzzer/FuzzedDataProvider.h>

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

  char* path = provider.ConsumeRandomLengthString().c_str();
  char* mode = provider.ConsumeRandomLengthString().c_str();
  char* opts = provider.ConsumeRandomLengthString().c_str();
  int fd = provider.ConsumeIntegral<int>();
  int flags = provider.ConsumeIntegral<int>();
  int mode2 = provider.ConsumeIntegral<int>();

  struct SDBStr_2311** names = nullptr;
  struct SDBStr_2311** vals = nullptr;
  int* fd2 = nullptr;

  size_t ret = s_open(path, mode, opts, fd, flags, mode2, &names, &vals, &fd2);

  if (names) {
    for (size_t i = 0; names[i]; i++) {
      free(names[i]);
    }
    free(names);
  }
  if (vals) {
    for (size_t i = 0; vals[i]; i++) {
      free(vals[i]);
    }
    free(vals);
  }
  if (fd2) {
    free(fd2);
  }

  free(path);
  free(mode);
  free(opts);

  return ret;
}