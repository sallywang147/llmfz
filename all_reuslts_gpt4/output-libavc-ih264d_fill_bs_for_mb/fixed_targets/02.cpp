#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ih264_typedefs.h"
#include "ih264d_structs.h"
#include "ih264d_defs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct deblk_mb_t ps_cur_mb_params;
  struct deblk_mb_t ps_top_mb_params;
  struct deblk_mb_t ps_left_mb_params;
  struct _mv_pred_t ps_cur_mv_pred;
  struct _mv_pred_t ps_top_mv_pred;
  struct _mv_pred_t ps_leftmost_mv_pred;
  struct neighbouradd_t ps_left_addr;
  struct neighbouradd_t ps_top_add;

  char puc_cur_nnz[16];
  char puc_top_nnz[16];
  char* ppv_map_ref_idx_to_poc[16];
  int ui_mbAff = stream.ConsumeIntegral<int>();
  int ui_bs_table[16];

  size_t consumed = stream.ConsumeData(&ps_cur_mb_params, sizeof(ps_cur_mb_params));
  if (consumed != sizeof(ps_cur_mb_params)) return 0;

  consumed = stream.ConsumeData(&ps_top_mb_params, sizeof(ps_top_mb_params));
  if (consumed != sizeof(ps_top_mb_params)) return 0;

  consumed = stream.ConsumeData(&ps_left_mb_params, sizeof(ps_left_mb_params));
  if (consumed != sizeof(ps_left_mb_params)) return 0;

  consumed = stream.ConsumeData(&ps_cur_mv_pred, sizeof(ps_cur_mv_pred));
  if (consumed != sizeof(ps_cur_mv_pred)) return 0;

  consumed = stream.ConsumeData(&ps_top_mv_pred, sizeof(ps_top_mv_pred));
  if (consumed != sizeof(ps_top_mv_pred)) return 0;

  consumed = stream.ConsumeData(&ps_leftmost_mv_pred, sizeof(ps_leftmost_mv_pred));
  if (consumed != sizeof(ps_leftmost_mv_pred)) return 0;

  consumed = stream.ConsumeData(&ps_left_addr, sizeof(ps_left_addr));
  if (consumed != sizeof(ps_left_addr)) return 0;

  consumed = stream.ConsumeData(&ps_top_add, sizeof(ps_top_add));
  if (consumed != sizeof(ps_top_add)) return 0;

  for (int i = 0; i < 16; i++) {
    ui_bs_table[i] = stream.ConsumeIntegral<int>();
    puc_cur_nnz[i] = stream.ConsumeIntegral<char>();
    puc_top_nnz[i] = stream.ConsumeIntegral<char>();
  }

  ih264d_fill_bs_for_mb(&ps_cur_mb_params, &ps_top_mb_params, &ps_left_mb_params, &ps_cur_mv_pred, &ps_top_mv_pred, puc_cur_nnz, puc_top_nnz, ppv_map_ref_idx_to_poc, ui_mbAff, ui_bs_table, &ps_leftmost_mv_pred, &ps_left_addr, &ps_top_add);

  return 0;
}