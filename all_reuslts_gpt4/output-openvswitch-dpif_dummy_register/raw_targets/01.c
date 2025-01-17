#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" void dpif_dummy_register(int level);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int level = stream.ConsumeIntegral<int>();
  dpif_dummy_register(level);
  return 0;
}