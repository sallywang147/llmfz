#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dwarf.h"

// Assume that func_type is a function pointer type that takes three arguments
typedef void (*func_type)(struct dwarf_cursor *, int, char *);

// Define a callback function to be passed to the target function
void callback(struct dwarf_cursor *c, int state, char *token) {
  // Do nothing
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Create a FuzzedDataProvider instance
  FuzzedDataProvider stream(data, size);

  // Define and initialize a struct dwarf_cursor
  struct dwarf_cursor cursor;
  cursor.loc = stream.ConsumeIntegral<uint64_t>();
  cursor.start = stream.ConsumeIntegral<uint64_t>();
  cursor.end = stream.ConsumeIntegral<uint64_t>();
  cursor.cfa = stream.ConsumeIntegral<uint64_t>();

  // Define and initialize a char pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *token = const_cast<char *>(str.c_str());

  // Call the function to be fuzzed
  dwarf_reg_states_table_iterate(&cursor, callback, token);

  return 0;
}