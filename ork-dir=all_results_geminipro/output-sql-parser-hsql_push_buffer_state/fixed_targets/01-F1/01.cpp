#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fuzzer/FuzzedDataProvider.h>
#include <string>

extern "C" {
#include "hsql_bison.h"
void hsql_push_buffer_state(struct yy_buffer_state*, char*);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input = stream.ConsumeRemainingBytesAsString();
  char* scanner = const_cast<char*>(input.c_str());
  hsql_push_buffer_state(nullptr, scanner);
  return 0;
}