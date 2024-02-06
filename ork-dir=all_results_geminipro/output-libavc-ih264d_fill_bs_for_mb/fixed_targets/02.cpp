#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "deblocking.h"
#include "mv_pred.h"
#include "nal_unit.h"
#include "picture.h"
#include "ref_list.h"
#include "slice.h"
}

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
  int ui_mbAff = stream.ConsumeIntegral<int>();
  int *ui_bs_table = stream.ConsumeIntegral<int*>();
  char *puc_cur_nnz = stream.ConsumeIntegral<char*>();
  char *puc_top_nnz = stream.ConsumeIntegral<char*>();
  char **ppv_map_ref_idx_to_poc = stream.ConsumeIntegral<char**>();
  int *p_top_poc = stream.ConsumeIntegral<int*>();
  int i_top_poc = *p_top_poc;

  ih264d_fill_bs_for_mb(&ps_cur_mb_params, &ps_top_mb_params, &ps_left_mb_params,
                        &ps_cur_mv_pred, &ps_top_mv_pred, puc_cur_nnz, puc_top_nnz,
                        ppv_map_ref_idx_to_poc, ui_mbAff, ui_bs_table,
                        &ps_leftmost_mv_pred, &ps_left_addr, &ps_top_add, &i_top_poc);
  return 0;
}