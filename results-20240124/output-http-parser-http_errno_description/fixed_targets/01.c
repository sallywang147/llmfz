#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "http_parser.h"
#include "fuzzer_utils.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const http_errno error_code = static_cast<http_errno>(stream.ConsumeIntegral<int>());
  char *error_description = http_errno_description(error_code);
  free(error_description);
  return 0;
}