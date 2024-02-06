#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int var_tmp_dir(char ** ret);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  char* dir = nullptr;
  int result = var_tmp_dir(&dir);

  if (dir != nullptr) {
    free(dir);
  }

  return 0;
}