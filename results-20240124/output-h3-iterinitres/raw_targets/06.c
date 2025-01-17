 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

struct IterCellsResolution {
  int resolution;
  int min_resolution;
  int max_resolution;
  int max_depth;
  int max_depth_limit;
  int max_depth_limit_default;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct IterCellsResolution res;
  res.resolution = stream.ConsumeIntegral<int>();
  res.min_resolution = stream.ConsumeIntegral<int>();
  res.max_resolution = stream.ConsumeIntegral<int>();
  res.max_depth = stream.ConsumeIntegral<int>();
  res.max_depth_limit = stream.ConsumeIntegral<int>();
  res.max_depth_limit_default = stream.ConsumeIntegral<int>();

  iterInitRes(&res, 0);
  return 0;
}