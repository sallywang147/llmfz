#include <cstdlib>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char *ret;
  int result = var_tmp_dir(&ret);
  if (result == 0) {
    free(ret);
  }
  return 0;
}