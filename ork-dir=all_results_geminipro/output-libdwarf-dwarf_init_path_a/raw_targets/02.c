#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "dwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string path = stream.ConsumeRemainingBytesAsString();
  char true_path_out_buffer[1024];
  memset(true_path_out_buffer, 0, sizeof(true_path_out_buffer));
  struct Dwarf_Debug_s* ret_dbg = nullptr;
  struct Dwarf_Error_s* error = nullptr;
  const int groupnumber = stream.ConsumeIntegral<int>();
  const int universalnumber = stream.ConsumeIntegral<int>();
  const func_type* errhand = nullptr;
  const char* errarg = nullptr;

  dwarf_init_path_a(const_cast<char*>(path.c_str()), true_path_out_buffer,
                    sizeof(true_path_out_buffer), groupnumber, universalnumber,
                    errhand, errarg, &ret_dbg, &error);
  if (ret_dbg) {
    dwarf_finish(ret_dbg, &error);
  }
  return 0;
}