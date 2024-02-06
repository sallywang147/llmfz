#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

void exercise_signature_key(int key, int usage, int alg) {
  // Do something with the key, usage, and alg.
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int key = stream.ConsumeIntegral<int>();
  const int usage = stream.ConsumeIntegral<int>();
  const int alg = stream.ConsumeIntegral<int>();
  exercise_signature_key(key, usage, alg);
  return 0;
}