#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <dwfl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  Dwfl_Module *module = dwfl_module_create_path(
      stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str());
  if (module == nullptr) {
    return 0;
  }

  Dwfl_Frame *frame = dwfl_frame_create();
  if (frame == nullptr) {
    dwfl_module_destroy(module);
    return 0;
  }

  dwfl_frame_pc(frame, nullptr, nullptr);

  dwfl_frame_destroy(frame);
  dwfl_module_destroy(module);
  return 0;
}