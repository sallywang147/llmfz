#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" {
#include "aom/aom_decoder.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for the function
  struct aom_codec_alg_priv *priv = nullptr;
  size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::string buffer1 = stream.ConsumeBytesAsString(buffer_size);
  std::string buffer2 = stream.ConsumeRemainingBytesAsString();

  // Call the function with the parameters
  int result = decoder_inspect(priv, const_cast<char*>(buffer1.c_str()), buffer_size, const_cast<char*>(buffer2.c_str()));

  return 0;
}