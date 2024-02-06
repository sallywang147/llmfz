#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" int var_tmp_dir(char ** ret);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  char* ret;
  var_tmp_dir(&ret);
  free(ret);
  return 0;
}