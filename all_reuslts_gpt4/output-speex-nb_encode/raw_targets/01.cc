#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "speex/speex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the Speex encoder.
  void* state = speex_encoder_init(&speex_nb_mode);
  if (state == nullptr) {
    return 0;
  }

  // Create a SpeexBits object.
  SpeexBits bits;
  speex_bits_init(&bits);

  // Consume the data for the vin parameter.
  std::vector<char> vin = stream.ConsumeBytes<char>(stream.remaining_bytes());

  // Call the function to be fuzzed.
  nb_encode(state, vin.data(), &bits);

  // Clean up.
  speex_bits_destroy(&bits);
  speex_encoder_destroy(state);

  return 0;
}