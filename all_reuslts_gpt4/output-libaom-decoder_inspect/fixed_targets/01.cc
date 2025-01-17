#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "aom/aom_decoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct aom_codec_alg_priv *priv = nullptr;
  size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string buffer = stream.ConsumeBytesAsString(buffer_size);
  char *buffer_ptr = const_cast<char*>(buffer.c_str());

  size_t detail_size = stream.remaining_bytes();
  std::string detail = stream.ConsumeRemainingBytesAsString();
  char *detail_ptr = const_cast<char*>(detail.c_str());

  int ret = decoder_inspect(priv, buffer_ptr, buffer_size, detail_ptr);

  return 0;
}