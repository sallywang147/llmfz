 #include <fuzzer/FuzzedDataProvider.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::string source = fdp.ConsumeRandomLengthString(256);
  ada_can_parse(source.data(), source.length());
  return 0;
}