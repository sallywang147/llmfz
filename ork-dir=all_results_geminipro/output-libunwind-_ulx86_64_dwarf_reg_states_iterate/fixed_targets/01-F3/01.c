#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include <libunwind.h>
#include <libunwind-x86_64.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a dwarf cursor.
  unw_cursor_t cursor;
  unw_getcontext(&cursor);
  unw_init_local(&cursor, NULL);

  // Create a callback function.
  auto callback = [](unw_word_t reg, unw_word_t val, void* arg) -> int {
    // Do something with the register and value.
    return 0;
  };

  // Iterate over the register states.
  int result = _ULx86_64_dwarf_reg_states_iterate(&cursor, callback, NULL);
  if (result != 0) {
    // An error occurred.
    return 0;
  }

  return 0;
}