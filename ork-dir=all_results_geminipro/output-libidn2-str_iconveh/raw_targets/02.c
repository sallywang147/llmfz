#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" char *str_iconveh(char *src, char *from_codeset, char *to_codeset,
                             int handler);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string src = stream.ConsumeRemainingBytesAsString();
  const std::string from_codeset =
      stream.ConsumeRandomLengthString(10, 30);  // 10-30 chars
  const std::string to_codeset =
      stream.ConsumeRandomLengthString(10, 30);  // 10-30 chars
  const int handler = stream.ConsumeIntegralInRange(0, 10);

  char *result = str_iconveh(const_cast<char *>(src.c_str()),
                            const_cast<char *>(from_codeset.c_str()),
                            const_cast<char *>(to_codeset.c_str()), handler);
  free(result);
  return 0;
}