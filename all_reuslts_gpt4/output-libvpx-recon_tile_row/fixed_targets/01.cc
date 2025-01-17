#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "vpx/vp8dx.h"
#include "vpx/vpx_decoder.h"
#include "vpx_ports/mem_ops.h"
#include "vpx/internal/vpx_codec_internal.h"
#include "vp9/decoder/vp9_decoder.h"
#include "vp9/decoder/vp9_decodeframe.h"
#include "vp9/decoder/vp9_thread.h"

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(VP9Decoder)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  VP9Decoder *pbi = (VP9Decoder *)stream.ConsumeBytes<uint8_t>(sizeof(VP9Decoder)).data();
  TileWorkerData *tile_data = (TileWorkerData *)stream.ConsumeBytes<uint8_t>(sizeof(TileWorkerData)).data();
  VP9LfSyncData *lf_sync = (VP9LfSyncData *)stream.ConsumeBytes<uint8_t>(sizeof(VP9LfSyncData)).data();

  int start = stream.ConsumeIntegralInRange<int>(0, 100);
  int stop = stream.ConsumeIntegralInRange<int>(start, 100);
  int row = stream.ConsumeIntegralInRange<int>(0, 100);

  recon_tile_row(tile_data, pbi, start, stop, lf_sync, row);

  return 0;
}