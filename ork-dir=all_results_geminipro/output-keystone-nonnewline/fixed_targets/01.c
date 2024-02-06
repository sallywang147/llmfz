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

extern "C" int nonnewline(parse* p) {
  size_t i = 0;
  while (i < p->str.size() && p->str[i] != '\n') {
    i++;
  }
  p->str = p->str.substr(0, i);
  return 0;
}

extern "C" void LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  parse p;
  p.str = provider.ConsumeRemainingBytesAsString();

  nonnewline(&p);
}