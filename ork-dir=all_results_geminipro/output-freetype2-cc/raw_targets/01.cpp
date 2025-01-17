#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  void* _GLOBAL__sub_I_ftfuzzer_cc = stream.ConsumeBytes<void>(size);
  _GLOBAL__sub_I_ftfuzzer_cc();
  return 0;
}