#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct Reclass {
    int dummy;
  };
  struct Reclass* cc = new struct Reclass;
  int c = stream.ConsumeIntegral<int>();
  int result = incclasscanon(cc, c);
  delete cc;
  return result;
}