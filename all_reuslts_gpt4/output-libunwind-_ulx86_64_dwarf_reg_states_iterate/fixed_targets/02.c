#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libunwind.h"

// Define a callback function to match the required type
void cb(const char *name, unw_word_t off, unw_word_t len, unw_word_t dwreg, unw_word_t when, char *token) {
  // Do nothing, just a placeholder
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the required structures
  unw_context_t uc;
  unw_cursor_t cursor;
  unw_getcontext(&uc);
  unw_init_local(&cursor, &uc);

  // Consume the remaining bytes as a string
  std::string token = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  _ULx86_64_dwarf_reg_states_iterate(&cursor, cb, const_cast<char*>(token.c_str()));

  return 0;
}