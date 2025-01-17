#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char* tmp_dir_path = nullptr;
  int ret = tmp_dir(&tmp_dir_path);
  free(tmp_dir_path);
  return ret;
}