#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "capstone/capstone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    cs_arch arch;
    cs_mode mode;
    cs_err err = cs_open(arch, mode, &handle);
    if (err) {
      return 0;
    }
    initialized = true;
  }

  struct cs_struct ud;
  ALPHA_global_init(&ud);

  FuzzedDataProvider provider(data, size);
  const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto next_input = provider.ConsumeBytes<uint8_t>(next_size);
  cs_disasm(handle, next_input.data(), next_input.size(), 0x1000, 0, &all_insn);

  cs_free(all_insn, count);
  cs_close(&handle);

  return 0;
}