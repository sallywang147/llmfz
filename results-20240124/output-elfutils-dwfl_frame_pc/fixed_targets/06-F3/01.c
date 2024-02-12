#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <libdwarf.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Dwfl_Module *module = dwfl_module_create_empty(DWFL_MODULE_LIBELF, 0);
  if (module == nullptr) {
    return 0;
  }

  Dwfl_Line *line = dwfl_line_alloc();
  if (line == nullptr) {
    dwfl_module_destroy(module);
    return 0;
  }

  Dwfl_Frame *frame = dwfl_frame_create(module, line, nullptr, nullptr, nullptr);
  if (frame == nullptr) {
    dwfl_line_free(line);
    dwfl_module_destroy(module);
    return 0;
  }

  size_t pc = stream.ConsumeIntegral<size_t>();
  char isactivation = stream.ConsumeIntegral<char>();
  bool ret = dwfl_frame_pc(frame, &pc, &isactivation);

  dwfl_frame_destroy(frame);
  dwfl_line_free(line);
  dwfl_module_destroy(module);

  return 0;
}