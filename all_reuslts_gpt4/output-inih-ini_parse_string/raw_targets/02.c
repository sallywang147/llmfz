#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ini.h"

int ini_handler(void* user, const char* section, const char* name, const char* value) {
  // This is a dummy handler function. It doesn't need to do anything.
  return 1;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRemainingBytesAsString();
  char* ptr = const_cast<char*>(str.c_str());

  ini_parse_string(ptr, ini_handler, nullptr);

  return 0;
}