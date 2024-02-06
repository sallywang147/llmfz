#include <fuzzer/FuzzedDataProvider.h>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<std::string> result;
  try {
    result = stream.ConsumeRemainingBytesAsVector<std::string>();
  } catch (...) {
  }
  return 0;
}