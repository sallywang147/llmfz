#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libunwind.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  unw_addr_space_t as = unw_local_addr_space;
  unw_cursor_t cursor;

  // Initialize the cursor to the context of the calling function.
  if (unw_init_local(&cursor, as) != 0) {
    return 0;
  }

  // Consume remaining bytes as a string to use as the argument.
  std::string arg = stream.ConsumeRemainingBytesAsString();

  // Call the function to be fuzzed.
  _ULx86_64_local_resume(as, &cursor, const_cast<char*>(arg.c_str()));

  return 0;
}