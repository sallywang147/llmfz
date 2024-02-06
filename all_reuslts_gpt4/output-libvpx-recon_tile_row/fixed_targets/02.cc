#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "vpx/vpx_decoder.h"
#include "vpx_ports/mem_ops.h"
#include "vp9/common/vp9_thread_common.h"
#include "vp9/decoder/vp9_decoder.h"
#include "vp9/decoder/vp9_dthread.h"

#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the TileWorkerData struct
  TileWorkerData tile_worker_data;
  tile_worker_data.td = reinterpret_cast<ThreadData *>(calloc(1, sizeof(ThreadData)));

  // Initialize the VP9Decoder struct
  VP9Decoder vp9_decoder;
  vp9_decoder.common = reinterpret_cast<VP9_COMMON *>(calloc(1, sizeof(VP9_COMMON)));

  // Initialize the VP9LfSyncData struct
  VP9LfSyncData vp9_lf_sync_data;

  // Extract integral values
  int start = stream.ConsumeIntegral<int>();
  int stop = stream.ConsumeIntegral<int>();
  int row = stream.ConsumeIntegral<int>();

  // Call the target function
  recon_tile_row(&tile_worker_data, &vp9_decoder, start, stop, &vp9_lf_sync_data, row);

  // Clean up
  free(tile_worker_data.td);
  free(vp9_decoder.common);

  return 0;
}