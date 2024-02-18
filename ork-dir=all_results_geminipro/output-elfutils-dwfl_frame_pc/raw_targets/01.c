#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "libunwind.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    unw_init_local(unw_local_addr_space, NULL);
    initialized = true;
  }

  unw_cursor_t cursor;
  unw_context_t uc;
  unw_getcontext(&uc);
  unw_init_local(&cursor, &uc);

  FuzzedDataProvider provider(data, size);

  size_t pc;
  char isactivation;
  while (unw_step(&cursor) > 0) {
    if (provider.remaining_bytes() == 0) {
      break;
    }
    const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
        0,
        provider.remaining_bytes());
    auto next_input = provider.ConsumeBytes<uint8_t>(next_size);
    dwfl_frame_pc(cursor.dwarf.frame, &pc, &isactivation);
  }

  return 0;
}