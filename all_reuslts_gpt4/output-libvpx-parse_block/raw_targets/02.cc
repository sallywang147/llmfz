#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "fuzzer/FuzzedDataProvider.h"
#include "vp9/common/vp9_tile_common.h"
#include "vp9/decoder/vp9_decoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct TileWorkerData tile_worker_data;
  struct VP9Decoder vp9_decoder;

  // Initialize the structures with zeroes
  memset(&tile_worker_data, 0, sizeof(tile_worker_data));
  memset(&vp9_decoder, 0, sizeof(vp9_decoder));

  int mi_row = stream.ConsumeIntegral<int>();
  int mi_col = stream.ConsumeIntegral<int>();
  char allow_hp = stream.ConsumeBool();
  int is_inter_block = stream.ConsumeBool();
  int seg_id_predicted = stream.ConsumeBool();

  parse_block(&tile_worker_data, &vp9_decoder, mi_row, mi_col, allow_hp, is_inter_block, seg_id_predicted);

  return 0;
}