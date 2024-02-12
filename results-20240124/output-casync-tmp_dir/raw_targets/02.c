 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char *ret = nullptr;
  const int ret_val = tmp_dir(&ret);
  if (ret_val != 0) {
    return 0;
  }
  free(ret);
  return 0;
}