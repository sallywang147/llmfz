#include "hsql_bison.h"
#include <string>

extern "C" {
#include <cstring>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  yy_buffer_state buffer = yy_scan_string(input.c_str());
  hsql_push_buffer_state(buffer, nullptr);
  yy_delete_buffer(buffer);
  return 0;
}