#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "speex/speex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t state_size = stream.ConsumeIntegralInRange<size_t>(
      0, 1 << 10);
  char* state = new char[state_size];
  stream.ConsumeBytes(state, state_size);

  const size_t vin_size = stream.ConsumeIntegralInRange<size_t>(
      0, 1 << 10);
  char* vin = new char[vin_size];
  stream.ConsumeBytes(vin, vin_size);

  SpeexBits bits;
  speex_bits_init(&bits);
  nb_encode(state, vin, &bits);
  speex_bits_destroy(&bits);

  delete[] state;
  delete[] vin;
  return 0;
}