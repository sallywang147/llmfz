#include <stddef.h>
#include <stdint.h>

#include "vp9/common/vp9_common.h"
#include "vp9/common/vp9_entropy.h"
#include "vp9/common/vp9_scan.h"
#include "vp9/common/vp9_seg_common.h"
#include "vp9/common/vp9_tokenenums.h"
#include "vp9/common/vp9_types_common.h"
#include "vp9/decoder/vp9_decodframe.h"
#include "vp9/decoder/vp9_decodemv.h"
#include "vp9/decoder/vp9_decoder.h"
#include "vp9/decoder/vp9_dthread.h"
#include "vp9/decoder/vp9_entropymode.h"
#include "vp9/decoder/vp9_onyxc_int.h"
#include "vp9/decoder/vp9_reader.h"
#include "vp9/decoder/vp9_threading.h"
#include "vpx_ports/mem_ops.h"

extern "C" {
#include "vp9/decoder/vp9_reconinter.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct VP9Decoder decoder;
  struct VP9LfSyncData lf_sync_data;
  struct TileWorkerData twd;
  if (size < sizeof(lf_sync_data)) {
    return 0;
  }
  memmove(&lf_sync_data, data, sizeof(lf_sync_data));
  data += sizeof(lf_sync_data);
  size -= sizeof(lf_sync_data);
  vp9_setup_past_independence(&decoder);
  recon_tile_row(&twd, &decoder, 0, 0, &lf_sync_data, 0);
  return 0;
}
}