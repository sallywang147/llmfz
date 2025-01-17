#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <regex.h>

struct parse {
  int dummy;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct parse p;
  int arg1 = stream.ConsumeIntegral<int>();
  int arg2 = stream.ConsumeIntegral<int>();

  p_bre(&p, arg1, arg2);

  return 0;
}