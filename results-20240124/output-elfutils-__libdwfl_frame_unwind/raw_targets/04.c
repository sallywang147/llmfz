 #include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct Dwfl_Frame state;
  state.state = stream.ConsumeIntegral<uint8_t>();
  state.cfa = stream.ConsumeIntegral<uint64_t>();
  state.pc = stream.ConsumeIntegral<uint64_t>();
  state.cfa_reg = stream.ConsumeIntegral<uint8_t>();
  state.cfa_offset = stream.ConsumeIntegral<uint64_t>();
  state.return_addr = stream.ConsumeIntegral<uint64_t>();
  state.prev_frame = nullptr;
  state.next_frame = nullptr;

  __libdwfl_frame_unwind(&state);

  return 0;
}