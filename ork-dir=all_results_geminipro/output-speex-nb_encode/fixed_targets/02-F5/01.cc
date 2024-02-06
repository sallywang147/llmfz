#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <vector>

extern "C" {
#include "speex/speex.h"
#include "speex/speex_nb.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t state_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* state = new char[state_size];
  stream.ConsumeBytes(state, state_size);

  const size_t vin_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* vin = new char[vin_size];
  stream.ConsumeBytes(vin, vin_size);

  SpeexBits bits;
  speex_bits_init(&bits);

  int ret = nb_encode(state, vin, &bits);
  if (ret != 0) {
    speex_bits_destroy(&bits);
    delete[] state;
    delete[] vin;
    return 0;
  }

  char* encoded = new char[bits.len];
  memcpy(encoded, bits.chars, bits.len);

  speex_bits_destroy(&bits);
  delete[] state;
  delete[] vin;
  delete[] encoded;
  return 0;
}