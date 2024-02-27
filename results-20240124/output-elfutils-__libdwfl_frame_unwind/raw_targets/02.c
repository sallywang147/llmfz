 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t slate_width = stream.ConsumeIntegral<uint8_t>();
  const uint8_t slate_height = stream.ConsumeIntegral<uint8_t>();
  Dwfl_Frame state;
  state.cfa = stream.ConsumeIntegral<uint64_t>();
  state.pc = stream.ConsumeIntegral<uint64_t>();
  state.fp = stream.ConsumeIntegral<uint64_t>();
  state.ra = stream.ConsumeIntegral<uint64_t>();
  state.cfa_valid = stream.ConsumeBool();
  state.pc_valid = stream.ConsumeBool();
  state.fp_valid = stream.ConsumeBool();
  state.ra_valid = stream.ConsumeBool();
  state.sp_valid = stream.ConsumeBool();
  state.sp = stream.ConsumeIntegral<uint64_t>();
  state.gr_count = stream.ConsumeIntegral<uint64_t>();
  state.gr = stream.ConsumeIntegral<uint64_t>();
  state.gr_valid = stream.ConsumeBool();
  state.gr_offs = stream.ConsumeIntegral<uint64_t>();
  state.gr_offs_valid = stream.ConsumeBool();
  state.gr_off_size = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_size_valid = stream.ConsumeBool();
  state.gr_off_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_count_valid = stream.ConsumeBool();
  state.gr_off_overflow = stream.ConsumeBool();
  state.gr_off_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_valid = stream.ConsumeBool();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count = stream.ConsumeIntegral<uint64_t>();
  state.gr_off_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit_overflow_count_limit