#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  BrotliBitReader bit_reader;
  BrotliInitBitReader(&bit_reader, data, size);

  while (stream.remaining_bytes() > 0) {
    size_t bits = stream.ConsumeIntegralInRange<size_t>(1, 32);
    size_t val = 0;

    BrotliSafeReadBits32Slow(&bit_reader, bits, &val);
  }

  return 0;
}