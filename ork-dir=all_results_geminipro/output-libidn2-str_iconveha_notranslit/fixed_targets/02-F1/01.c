#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <iconv.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string src = stream.ConsumeRemainingBytesAsString();
  const std::string from_codeset = stream.ConsumeBytesAsString(10);
  const std::string to_codeset = stream.ConsumeBytesAsString(10);
  const int handler = stream.ConsumeIntegral<int>();

  char* result = str_iconveha_notranslit(
      const_cast<char*>(src.c_str()), const_cast<char*>(from_codeset.c_str()),
      const_cast<char*>(to_codeset.c_str()), handler);
  free(result);

  return 0;
}