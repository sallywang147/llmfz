#include <fuzzer/FuzzedDataProvider.h>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char* tmp_dir_result;
  int ret = tmp_dir(&tmp_dir_result);
  free(tmp_dir_result);
  return ret;
}