#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "libdwfl.h"

extern "C" {
int __libdwfl_frame_unwind(Dwfl_Frame* state);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  Dwfl_Frame state;
  memset(&state, 0, sizeof(state));

  state.stack_size = stream.ConsumeIntegral<uint64_t>();
  state.stack_base = stream.ConsumeIntegral<uint64_t>();
  state.stack_top = state.stack_base + state.stack_size;
  state.cfa = stream.ConsumeIntegral<uint64_t>();
  state.pc = stream.ConsumeIntegral<uint64_t>();
  state.ip = stream.ConsumeIntegral<uint64_t>();
  state.lsda = stream.ConsumeIntegral<uint64_t>();
  state.cfi_addr = stream.ConsumeIntegral<uint64_t>();
  state.cfi_size = stream.ConsumeIntegral<uint64_t>();
  state.lsda_addr = stream.ConsumeIntegral<uint64_t>();
  state.lsda_size = stream.ConsumeIntegral<uint64_t>();
  state.cfa_reg = stream.ConsumeIntegral<uint64_t>();
  state.cfa_off = stream.ConsumeIntegral<uint64_t>();
  state.same_fp = stream.ConsumeIntegral<uint64_t>();
  state.call_frame_addr = stream.ConsumeIntegral<uint64_t>();
  state.call_frame_size = stream.ConsumeIntegral<uint64_t>();
  state.return_addr = stream.ConsumeIntegral<uint64_t>();
  state.fde_addr = stream.ConsumeIntegral<uint64_t>();
  state.fde_size = stream.ConsumeIntegral<uint64_t>();
  state.fde_offset = stream.ConsumeIntegral<uint64_t>();
  state.eh_frame_hdr = stream.ConsumeIntegral<uint64_t>();
  state.eh_frame_hdr_size = stream.ConsumeIntegral<uint64_t>();
  state.lsda_section_offset = stream.ConsumeIntegral<uint64_t>();
  state.lsda_section_size = stream.ConsumeIntegral<uint64_t>();
  state.lsda_section_data = stream.ConsumeRemainingBytes<uint8_t>();

  __libdwfl_frame_unwind(&state);
  return 0;
}