#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string input = stream.ConsumeRemainingBytesAsString();

  ada_can_parse(input.data(), input.size());

  return 0;
}