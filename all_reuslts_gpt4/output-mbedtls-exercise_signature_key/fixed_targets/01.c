#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int key = stream.ConsumeIntegral<int>();
  int usage = stream.ConsumeIntegral<int>();
  int alg = stream.ConsumeIntegral<int>();

  exercise_signature_key(key, usage, alg);

  return 0;
}