#include <cstddef>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include <string>

extern "C" {
#include <libFuzzer/libFuzzer.h>
}

struct parse {
  std::string str;
};

extern "C" void LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  parse p;
  p.str = provider.ConsumeRemainingBytesAsString();

  nonnewline(&p);
}