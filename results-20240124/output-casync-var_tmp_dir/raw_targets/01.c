 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char* tmp_dir = nullptr;
  int ret = var_tmp_dir(&tmp_dir);
  free(tmp_dir);
  return ret;
}