#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int st = stream.ConsumeIntegral<int>();
  int flags = stream.ConsumeIntegral<int>();

  TPM2_ValidateState(st, flags);

  return 0;
}