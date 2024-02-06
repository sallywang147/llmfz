#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" char * decode_tiles_mt(struct AV1Decoder *, char *, char *, int, int);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 100) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  char *input_buffer = provider.ConsumeBytes<char>(size).data();
  int tile_cols = provider.ConsumeIntegralInRange<int>(1, 100);
  int tile_rows = provider.ConsumeIntegralInRange<int>(1, 100);

  char *output_buffer = decode_tiles_mt(nullptr, input_buffer, input_buffer + size,
                                        tile_cols, tile_rows);
  free(output_buffer);

  return 0;
}