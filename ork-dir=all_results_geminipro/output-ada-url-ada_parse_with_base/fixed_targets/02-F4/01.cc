#include <fuzzer/FuzzedDataProvider.h>
#include <memory>
#include <string>

extern "C" {
#include "ada_parse.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::string input = fdp.ConsumeRandomLengthString(256);
  std::string base = fdp.ConsumeRandomLengthString(256);

  char *input_ptr = input.data();
  char *base_ptr = base.data();

  ada_parse_with_base(input_ptr, input.size(), base_ptr, base.size());

  return 0;
} // extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {