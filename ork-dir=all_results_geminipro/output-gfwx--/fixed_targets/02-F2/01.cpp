#include <fuzzer/FuzzedDataProvider.h>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<std::string> vec;
  try {
    vec = stream.ConsumeVector<std::string>();
  } catch (FuzzedDataProvider::ConsumeError &e) {
  }
  return 0;
}