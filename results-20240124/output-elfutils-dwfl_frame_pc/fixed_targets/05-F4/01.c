#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" {
#include <libunwind.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct Dwfl_Frame* frame = dwfl_begin_frame();
  if (frame == nullptr) {
    return 0;
  }

  size_t pc = stream.ConsumeIntegral<size_t>();
  char isactivation = stream.ConsumeIntegral<char>();
  dwfl_frame_pc(frame, &pc, &isactivation);

  dwfl_end_frame(frame);
  return 0;
}