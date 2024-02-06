#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "LzmaEnc.h"
#include "LzmaLib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 5) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize the encoder properties.
  CLzmaEncProps props;
  LzmaEncProps_Init(&props);
  props.level = stream.ConsumeIntegralInRange<int>(0, 9);
  props.dictSize = stream.ConsumeIntegralInRange<unsigned int>(0, 1 << 30);
  props.lc = stream.ConsumeIntegralInRange<int>(0, 8);
  props.lp = stream.ConsumeIntegralInRange<int>(0, 4);
  props.pb = stream.ConsumeIntegralInRange<int>(0, 4);
  props.fb = stream.ConsumeIntegralInRange<int>(5, 273);
  props.numThreads = stream.ConsumeIntegralInRange<int>(1, 2);

  // Initialize the encoder.
  ISzAlloc allocator = {SzAlloc, SzFree};
  CLzmaEncHandle encoder = LzmaEnc_Create(&allocator);
  if (encoder == 0) {
    return 0;
  }
  if (LzmaEnc_SetProps(encoder, &props) != SZ_OK) {
    LzmaEnc_Destroy(encoder, &allocator, &allocator);
    return 0;
  }

  // Prepare the input and output buffers.
  size_t srcLen = stream.remaining_bytes();
  size_t destLen = srcLen + srcLen / 3 + 128;
  std::vector<char> src = stream.ConsumeRemainingBytes<char>();
  std::vector<char> dest(destLen);

  // Encode the data.
  size_t propsSize = LZMA_PROPS_SIZE;
  std::vector<char> propsEncoded(LZMA_PROPS_SIZE);
  int result = LzmaEncode(dest.data(), &destLen, src.data(), srcLen, &props,
                          propsEncoded.data(), &propsSize, 0, nullptr,
                          &allocator, &allocator);
  if (result != SZ_OK) {
    LzmaEnc_Destroy(encoder, &allocator, &allocator);
    return 0;
  }

  LzmaEnc_Destroy(encoder, &allocator, &allocator);
  return 0;
}