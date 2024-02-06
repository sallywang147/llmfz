#include <fuzzer/FuzzedDataProvider.h>
#include <speex/speex.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0; // Not enough data to proceed.
  }

  FuzzedDataProvider stream(data, size);

  // Initialize Speex encoder.
  void *state = speex_encoder_init(&speex_nb_mode);
  if (!state) {
    return 0;
  }

  // Initialize Speex bits.
  SpeexBits bits;
  speex_bits_init(&bits);

  // Consume data for vin.
  std::string vin = stream.ConsumeBytesAsString(stream.remaining_bytes());

  // Call the function under test.
  int result = sb_encode((char*)state, (char*)vin.c_str(), &bits);

  // Cleanup.
  speex_bits_destroy(&bits);
  speex_encoder_destroy(state);

  return 0;
}