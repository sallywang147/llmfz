#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "libunwind.h"

// Dummy callback function
int dummy_callback(struct dwarf_cursor * c, char * token) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize a dummy dwarf_cursor
  struct dwarf_cursor c;

  // Prepare a random string token
  std::string token = stream.ConsumeRandomLengthString();
  
  // Call the function with the dummy cursor, callback and token
  _ULx86_64_dwarf_reg_states_iterate(&c, dummy_callback, token.data());

  return 0;
}