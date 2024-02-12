#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

extern "C" {
#include <unistd.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char *ret;
  int code = tmp_dir(&ret);
  if (code == 0) {
    free(ret);
  }
  return 0;
}