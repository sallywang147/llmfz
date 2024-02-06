#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    libdwarf_init(0, 0);
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  Dwfl_Module* module = dwfl_module_create_empty(DWFL_MODULE_LIBDW);
  Dwfl_Line* line;
  Dwfl_Line* prev_line = nullptr;
  Dwfl_Frame* frame = dwfl_frame_create();

  while (provider.remaining_bytes() > 0) {
    uint32_t addr = provider.ConsumeIntegral<uint32_t>();
    line = dwfl_add_line(module, addr, "file", 0);
    if (prev_line != nullptr) {
      dwfl_add_frame(frame, prev_line, line, nullptr, nullptr);
    }
    prev_line = line;
  }

  __libdwfl_frame_unwind(frame);

  dwfl_module_destroy(module);
  dwfl_frame_destroy(frame);

  return 0;
}