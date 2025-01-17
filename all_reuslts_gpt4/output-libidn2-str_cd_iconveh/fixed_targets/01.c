#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

#include "iconveh.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extracting parameters for str_cd_iconveh
  std::string src = stream.ConsumeRandomLengthString();
  struct iconveh_t cd;
  int handler = stream.ConsumeIntegral<int>();

  // Initializing iconveh_t structure
  cd.cd_min = stream.ConsumeIntegral<int>();
  cd.cd_max = stream.ConsumeIntegral<int>();
  cd.cd_flag = stream.ConsumeIntegral<int>();

  // Calling the target function
  char* result = str_cd_iconveh(const_cast<char*>(src.c_str()), &cd, handler);

  return 0;
}