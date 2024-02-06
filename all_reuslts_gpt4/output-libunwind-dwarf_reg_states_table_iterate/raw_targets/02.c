#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dwarf.h"

// Define a callback function to be used with dwarf_reg_states_table_iterate
int callback_func(struct dwarf_cursor * c, char * token) {
  // This is a dummy function. In a real-world scenario, you would perform some
  // operation on the cursor and token.
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a dummy dwarf_cursor struct
  struct dwarf_cursor cursor;

  // Define the callback function
  func_type * cb = callback_func;

  // Consume some bytes to create a token
  std::string token = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  dwarf_reg_states_table_iterate(&cursor, cb, const_cast<char *>(token.c_str()));

  return 0;
}