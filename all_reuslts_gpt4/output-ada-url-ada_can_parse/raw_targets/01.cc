#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::string input = provider.ConsumeRemainingBytesAsString();
  ada_can_parse(input.c_str(), input.size());

  return 0;
}