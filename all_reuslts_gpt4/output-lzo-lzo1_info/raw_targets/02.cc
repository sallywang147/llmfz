#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" size_t lzo1_info(int * rbits, int * clevel);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int rbits = stream.ConsumeIntegral<int>();
  int clevel = stream.ConsumeIntegral<int>();

  lzo1_info(&rbits, &clevel);

  return 0;
}