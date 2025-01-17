 #include <cstdint>
#include <cstdlib>
#include <string>

#include "http_parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int error_code = stream.ConsumeIntegral<int>();
  char *error_description = http_errno_description(error_code);
  free(error_description);
  return 0;
}