#include <cstddef>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include <map>

extern "C" {
struct anon {
  static size_t drop_deletes_without_resize(size_t pos) const { return 0; }
};

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::map<uint32_t, int> m;
  const size_t num_items = fdp.ConsumeIntegral<size_t>();
  for (size_t i = 0; i < num_items; ++i) {
    m[fdp.ConsumeIntegral<uint32_t>()] = fdp.ConsumeIntegral<int32_t>();
  }
  anon a;
  a.drop_deletes_without_resize(fdp.ConsumeIntegral<size_t>() % m.size());
  return 0;
}
}