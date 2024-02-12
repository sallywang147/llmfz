#include <fuzzer/FuzzedDataProvider.h>
#include <string>
#include "ada_parser.h" // Include the header file containing the declaration of ada_can_parse

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::string source = fdp.ConsumeRandomLengthString(256);
  ada_can_parse(source.data(), source.length()); // Use the ada_can_parse function
  return 0;
}