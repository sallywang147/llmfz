#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "fuzzer/FuzzedDataProvider.h"
#include "vp9/common/vp9_blockd.h"
#include "vp9/common/vp9_tile_common.h"
#include "vp9/decoder/vp9_decoder.h"
#include "vp9/decoder/vp9_dthread.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the VP9Decoder and TileWorkerData structs.
  VP9Decoder *pbi = vp9_decoder_create();
  if (!pbi) return 0;
  TileWorkerData *const tile_data = vp9_tile_worker_data_alloc(pbi);
  if (!tile_data) {
    vp9_decoder_remove(pbi);
    return 0;
  }

  // Consume data from the fuzzer input.
  int mi_row = stream.ConsumeIntegral<int>();
  int mi_col = stream.ConsumeIntegral<int>();
  char allow_update_cdf = stream.ConsumeIntegral<char>();
  int tile_row = stream.ConsumeIntegral<int>();
  int tile_col = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed.
  parse_block(tile_data, pbi, mi_row, mi_col, allow_update_cdf, tile_row, tile_col);

  // Cleanup.
  vp9_tile_worker_data_free(tile_data);
  vp9_decoder_remove(pbi);

  return 0;
}