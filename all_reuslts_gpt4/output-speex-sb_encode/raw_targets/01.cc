#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "speex/speex.h"
#include "speex/speex_bits.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize encoder
  int modeID = SPEEX_MODEID_NB;
  const SpeexMode *mode = speex_lib_get_mode(modeID);
  void *state = speex_encoder_init(mode);

  // Initialize bits
  SpeexBits bits;
  speex_bits_init(&bits);

  // Consume data for vin
  std::string vin = stream.ConsumeRandomLengthString();
  char *vin_ptr = const_cast<char *>(vin.c_str());

  // Call the function under test
  int result = sb_encode(state, vin_ptr, &bits);

  // Cleanup
  speex_bits_destroy(&bits);
  speex_encoder_destroy(state);

  return 0;
}