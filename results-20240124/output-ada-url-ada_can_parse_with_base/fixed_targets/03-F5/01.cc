#include <fuzzer/FuzzedDataProvider.h>
#include <string>

extern "C" {
#include "ada_parser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::string input = fdp.ConsumeRandomLengthString(256);
  std::string base = fdp.ConsumeRandomLengthString(256);

  bool result = ada_can_parse_with_base(input.data(), input.size(), base.data(),
                                       base.size());
  return 0;
}