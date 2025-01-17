#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "speex/speex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize an encoder state in narrowband mode
  void *state = speex_encoder_init(&speex_nb_mode);

  // Set the quality to maximum
  int tmp = 10;
  speex_encoder_ctl(state, SPEEX_SET_QUALITY, &tmp);

  // Initialization of the structure that holds the bits
  SpeexBits bits;
  speex_bits_init(&bits);

  // Consume data for 'vin' from the fuzzer input
  std::string vin = stream.ConsumeRemainingBytesAsString();
  
  // Call the function to be fuzzed
  nb_encode((char *)state, (char *)vin.c_str(), &bits);

  // Destroy the encoder state
  speex_encoder_destroy(state);

  // Destroy the bit-packing struct
  speex_bits_destroy(&bits);

  return 0;
}