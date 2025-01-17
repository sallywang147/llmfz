#include <fuzzer/FuzzedDataProvider.h>

extern "C" size_t FC_Initialize(char *path) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string path = provider.ConsumeRandomLengthString();
  FC_Initialize(path.c_str());
  return 0;
}