#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <unistd.h>
#include <tmp_dir.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char *ret = nullptr;
  tmp_dir(&ret);
  free(ret);
  return 0;
}