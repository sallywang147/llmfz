 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "libdwfl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const uint64_t ip = stream.ConsumeIntegral<uint64_t>();
  const uint64_t sp = stream.ConsumeIntegral<uint64_t>();
  const uint64_t fp = stream.ConsumeIntegral<uint64_t>();
  const uint64_t pc = stream.ConsumeIntegral<uint64_t>();
  const uint64_t cfa = stream.ConsumeIntegral<uint64_t>();
  const uint64_t ra = stream.ConsumeIntegral<uint64_t>();
  const uint64_t flags = stream.ConsumeIntegral<uint64_t>();

  Dwfl_Frame state;
  memset(&state, 0, sizeof(state));
  state.ip = ip;
  state.sp = sp;
  state.fp = fp;
  state.pc = pc;
  state.cfa = cfa;
  state.ra = ra;
  state.flags = flags;

  __libdwfl_frame_unwind(&state);

  return 0;
}