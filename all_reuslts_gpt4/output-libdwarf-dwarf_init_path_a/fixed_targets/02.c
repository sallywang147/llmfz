#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libdwarf.h"

// Error handler function
void errhand(Dwarf_Error error, Dwarf_Ptr errarg) {
    // Do nothing
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int groupnumber = stream.ConsumeIntegral<int>();
  int universalnumber = stream.ConsumeIntegral<int>();
  
  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string path = stream.ConsumeRandomLengthString();
  char *path_ptr = path.c_str();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string errarg = stream.ConsumeRandomLengthString();
  char *errarg_ptr = errarg.c_str();

  // Define other required variables
  char true_path_out_buffer[256] = {0};
  int true_path_bufferlen = sizeof(true_path_out_buffer);
  struct Dwarf_Debug_s* ret_dbg = nullptr;
  struct Dwarf_Error_s* error = nullptr;

  // Call the function to fuzz
  int result = dwarf_init_path_a(path_ptr, true_path_out_buffer, true_path_bufferlen, groupnumber, universalnumber, errhand, errarg_ptr, &ret_dbg, &error);

  // Clean up
  if (ret_dbg != nullptr) {
    dwarf_finish(ret_dbg, &error);
  }

  return 0;
}