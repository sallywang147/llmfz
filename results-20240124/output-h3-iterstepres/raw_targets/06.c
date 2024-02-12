#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "iter.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct IterCellsResolution itR;
  itR.x = stream.ConsumeIntegral<int64_t>();
  itR.y = stream.ConsumeIntegral<int64_t>();
  itR.z = stream.ConsumeIntegral<int64_t>();
  itR.res = stream.ConsumeIntegral<int32_t>();
  itR.res_cur = stream.ConsumeIntegral<int32_t>();
  itR.level = stream.ConsumeIntegral<int32_t>();
  itR.level_cur = stream.ConsumeIntegral<int32_t>();
  itR.next_level = stream.ConsumeIntegral<int32_t>();
  itR.next_level_cur = stream.ConsumeIntegral<int32_t>();
  itR.next_level_start = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_inc = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_inc_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_inc = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_inc_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_dec = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_dec_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_dec = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_dec_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_inc_dec = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_inc_dec_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_inc_dec = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_inc_dec_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_dec_inc = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_dec_inc_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_dec_inc = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_dec_inc_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_dec_dec = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_dec_dec_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_dec_dec = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_dec_dec_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_inc_dec_dec = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_inc_dec_dec_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_inc_dec_dec = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_inc_dec_dec_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_dec_inc_dec = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_dec_inc_dec_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_dec_inc_dec = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_dec_inc_dec_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_dec_dec_inc = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_dec_dec_inc_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_dec_dec_inc = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_dec_dec_inc_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_dec_dec_dec = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_start_dec_dec_dec_cur = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_dec_dec_dec = stream.ConsumeIntegral<uint64_t>();
  itR.next_level_end_dec_dec_dec_cur = stream.ConsumeIntegral<uint64_t>();
  iterStepRes(&itR);
  return 0;
}