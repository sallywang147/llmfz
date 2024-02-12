#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <libunwind.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct Dwfl_Frame state;
  memset(&state, 0, sizeof(state));

  state.version = stream.ConsumeIntegral<uint32_t>();
  state.cfa = stream.ConsumeIntegral<uint64_t>();
  state.pc = stream.ConsumeIntegral<uint64_t>();
  state.ip = stream.ConsumeIntegral<uint64_t>();
  state.fp = stream.ConsumeIntegral<uint64_t>();
  state.ra = stream.ConsumeIntegral<uint64_t>();
  state.sp = stream.ConsumeIntegral<uint64_t>();
  state.lr = stream.ConsumeIntegral<uint64_t>();
  state.type = stream.ConsumeIntegral<uint32_t>();
  state.lsda = stream.ConsumeIntegral<uint64_t>();
  state.cfa_offset = stream.ConsumeIntegral<uint32_t>();
  state.pc_offset = stream.ConsumeIntegral<uint32_t>();
  state.ip_offset = stream.ConsumeIntegral<uint32_t>();
  state.fp_offset = stream.ConsumeIntegral<uint32_t>();
  state.ra_offset = stream.ConsumeIntegral<uint32_t>();
  state.sp_offset = stream.ConsumeIntegral<uint32_t>();
  state.lr_offset = stream.ConsumeIntegral<uint32_t>();

  __libdwfl_frame_unwind(&state);
  return 0;
}