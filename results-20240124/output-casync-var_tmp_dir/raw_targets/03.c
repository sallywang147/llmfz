 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char* result;
  int ret = var_tmp_dir(&result);
  if (ret != 0) {
    return 0;
  }
  free(result);
  return 0;
}