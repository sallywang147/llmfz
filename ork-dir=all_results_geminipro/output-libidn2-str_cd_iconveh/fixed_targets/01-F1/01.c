#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include <iconv.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string src = stream.ConsumeRemainingBytesAsString();
  struct iconveh_t cd;
  memset(&cd, 0, sizeof(cd));
  const int handler = stream.ConsumeIntegral<int>();
  char* result = str_cd_iconveh(const_cast<char*>(src.c_str()), &cd, handler);
  free(result);
  return 0;
}