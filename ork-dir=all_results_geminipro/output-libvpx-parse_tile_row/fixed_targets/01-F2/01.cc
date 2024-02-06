#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "vpx/vpx_decoder.h"
#include "vpx_ports/mem_ops.h"

#include <fuzzer/FuzzedDataProvider.h>

typedef struct TileWorkerData {
  int start;
  int end;
  int tile_row;
  int tile_col;
  int tile_size;
  int tile_width;
  int tile_height;
  int mi_col_start;
  int mi_col_end;
  int mi_row_start;
  int mi_row_end;
  int mi_cols;
  int mi_rows;
  int sb_cols;
  int sb_rows;
  int sb_mi_size;
  int log2_tile_cols;
  int log2_tile_rows;
  int tile_list_count;
  int tile_list_size;
  int tile_list_start;
  int tile_list_end;
  int tile_list_offset;
  int tile_list_offset_end;
  int tile_list_offset_start;
  int tile_list_offset_size;
  int tile_list_offset_stride;
  int tile_list_offset_tile_size;
  int tile_list_offset_tile_stride;
  int tile_list_offset_tile_start;
  int tile_list_offset_tile_end;
  int tile_list_offset_tile_offset;
  int tile_list_offset_tile_offset_end;
  int tile_list_offset_tile_offset_start;
  int tile_list_offset_tile_offset_size;
  int tile_list_offset_tile_offset_stride;
  int tile_list_offset_tile_offset_tile_size;
  int tile_list_offset_tile_offset_tile_stride;
  int tile_list_offset_tile_offset_tile_start;
  int tile_list_offset_tile_offset_tile_end;
  int tile_list_offset_tile_offset_tile_offset;
  int tile_list_offset_tile_offset_tile_offset_end;
  int tile_list_offset_tile_offset_tile_offset_start;
  int tile_list_offset_tile_offset_tile_offset_size;
  int tile_list_offset_tile_offset_tile_offset_stride;
  int tile_list_offset_tile_offset_tile_offset_tile_size;
  int tile_list_offset_tile_offset_tile_offset_tile_stride;
  int tile_list_offset_tile_offset_tile_offset_tile_start;
  int tile_list_offset_tile_offset_tile_offset_tile_end;
  int tile_list_offset_tile_offset_tile_offset_tile_offset;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_end;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_start;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_size;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_stride;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_size;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_stride;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_start;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_end;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_end;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_start;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_size;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_stride;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_size;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_stride;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_start;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_end;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_offset;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_offset_end;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_offset_start;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_offset_size;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_offset_stride;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_size;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_stride;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_start;
  int tile_list_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_offset_tile_end;
} TileWorkerData;

extern "C" {
void parse_tile_row(TileWorkerData *tw, VP9Decoder *decoder, int tile_row, int tile_col,
                   char **end_ptr);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  TileWorkerData tw;
  memset(&tw, 0, sizeof(tw));
  VP9Decoder decoder;
  memset(&decoder, 0, sizeof(decoder));
  parse_tile_row(&tw, &decoder, fdp.ConsumeIntegral<int>(), fdp.ConsumeIntegral<int>(),
                 NULL);
  return 0;
}