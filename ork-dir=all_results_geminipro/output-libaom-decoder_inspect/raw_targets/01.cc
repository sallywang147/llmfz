#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "aom/aom_decoder.h"
#include "aom/aomdx.h"
#include "aom_ports/mem_ops.h"
#include "config/aom_config.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    aom_codec_dec_init(nullptr, nullptr, nullptr, 0);
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  const size_t max_buffer_size = 1 << 20;
  std::vector<uint8_t> buffer(provider.ConsumeIntegralInRange<size_t>(
      0, std::min(max_buffer_size, provider.remaining_bytes())));
  provider.ConsumeBytes<uint8_t>(buffer.data(), buffer.size());

  decoder_inspect(nullptr, reinterpret_cast<char*>(buffer.data()), buffer.size(),
                  nullptr);

  return 0;
}