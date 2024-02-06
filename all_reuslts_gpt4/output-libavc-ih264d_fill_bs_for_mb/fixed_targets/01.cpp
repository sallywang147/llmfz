#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ih264d_structs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  deblk_mb_t cur_mb_params;
  deblk_mb_t top_mb_params;
  deblk_mb_t left_mb_params;
  _mv_pred_t cur_mv_pred;
  _mv_pred_t top_mv_pred;
  _mv_pred_t leftmost_mv_pred;
  neighbouradd_t left_addr;
  neighbouradd_t top_addr;

  size_t consumed = stream.ConsumeData(&cur_mb_params, sizeof(cur_mb_params));
  consumed += stream.ConsumeData(&top_mb_params, sizeof(top_mb_params));
  consumed += stream.ConsumeData(&left_mb_params, sizeof(left_mb_params));
  consumed += stream.ConsumeData(&cur_mv_pred, sizeof(cur_mv_pred));
  consumed += stream.ConsumeData(&top_mv_pred, sizeof(top_mv_pred));
  consumed += stream.ConsumeData(&leftmost_mv_pred, sizeof(leftmost_mv_pred));
  consumed += stream.ConsumeData(&left_addr, sizeof(left_addr));
  consumed += stream.ConsumeData(&top_addr, sizeof(top_addr));

  if (consumed != sizeof(cur_mb_params) + sizeof(top_mb_params) + sizeof(left_mb_params) + sizeof(cur_mv_pred) + sizeof(top_mv_pred) + sizeof(leftmost_mv_pred) + sizeof(left_addr) + sizeof(top_addr)) {
    return 0;
  }

  std::vector<char> cur_nnz = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange<size_t>(0, 16));
  std::vector<char> top_nnz = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange<size_t>(0, 16));
  std::vector<int> bs_table = stream.ConsumeBytes<int>(stream.ConsumeIntegralInRange<size_t>(0, 16));
  std::vector<char*> map_ref_idx_to_poc = stream.ConsumeBytes<char*>(stream.ConsumeIntegralInRange<size_t>(0, 16));

  int mbAff = stream.ConsumeIntegral<int>();

  ih264d_fill_bs_for_mb(&cur_mb_params, &top_mb_params, &left_mb_params, &cur_mv_pred, &top_mv_pred, cur_nnz.data(), top_nnz.data(), map_ref_idx_to_poc.data(), mbAff, bs_table.data(), &leftmost_mv_pred, &left_addr, &top_addr);

  return 0;
}