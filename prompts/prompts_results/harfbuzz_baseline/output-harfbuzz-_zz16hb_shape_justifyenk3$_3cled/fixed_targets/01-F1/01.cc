#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <string>

class const_ {
 public:
  double operator()(double d) {
    return d;
  }
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  double d = stream.ConsumeFloatingPoint<double>();
  const_ c;
  c(d);
  return 0;
}