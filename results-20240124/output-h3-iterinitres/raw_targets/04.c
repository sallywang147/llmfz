 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

struct IterCellsResolution {
  int64_t x;
  int64_t y;
  int64_t z;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct IterCellsResolution res;
  iterInitRes(&res, stream.ConsumeIntegral<int>());
  return 0;
}