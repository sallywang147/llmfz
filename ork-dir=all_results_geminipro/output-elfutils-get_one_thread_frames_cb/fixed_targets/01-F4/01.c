#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <libdwarf.h>

extern "C" {
#include <libdwarf/dwarf_threads.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    // Initialize libdwarf.
    if (dwarf_init(0, DW_DLC_READ) != 0) {
      return 0;
    }
    initialized = true;
  }

  // Create a FuzzedDataProvider object to parse the input data.
  FuzzedDataProvider provider(data, size);

  // Consume a random number of bytes to use as the argument to
  // get_one_thread_frames_cb.
  size_t arg_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<uint8_t> arg_data = provider.ConsumeBytes<uint8_t>(arg_size);

  // Create a Dwfl_Thread object to pass to get_one_thread_frames_cb.
  Dwfl_Thread thread;
  memset(&thread, 0, sizeof(thread));

  // Call get_one_thread_frames_cb with the randomly generated argument.
  int result = dwarf_get_one_thread_frames_cb(&thread, reinterpret_cast<char*>(arg_data.data()));

  // Clean up libdwarf.
  dwarf_finish();

  return 0;
}