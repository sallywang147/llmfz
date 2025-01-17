#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libdwarf.h"

// Error handler
void errhand(Dwarf_Error error, Dwarf_Ptr errarg) {
    // Handle error
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    dwarf_init();
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  // Consume data for parameters
  std::string path = stream.ConsumeRandomLengthString();
  int true_path_bufferlen = stream.ConsumeIntegral<int>();
  std::vector<char> true_path_out_buffer(true_path_bufferlen);
  int groupnumber = stream.ConsumeIntegral<int>();
  int universalnumber = stream.ConsumeIntegral<int>();
  char * errarg = stream.ConsumeRandomLengthString().c_str();
  struct Dwarf_Debug_s * ret_dbg = nullptr;
  struct Dwarf_Error_s * error = nullptr;

  // Call the target function
  int ret = dwarf_init_path_a(path.c_str(), true_path_out_buffer.data(), true_path_bufferlen, groupnumber, universalnumber, errhand, errarg, &ret_dbg, &error);

  // Clean up
  if (ret_dbg != nullptr) {
    dwarf_finish(ret_dbg, &error);
  }

  return 0;
}