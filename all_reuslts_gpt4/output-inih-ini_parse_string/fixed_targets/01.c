#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ini.h"

static int fuzzing_handler(void* user, const char* section, const char* name,
                           const char* value) {
  // We don't actually care about the parsed values, we're just fuzzing.
  return 1;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  char* ptr = const_cast<char*>(str.c_str());

  ini_parse_string(ptr, fuzzing_handler, nullptr);

  return 0;
}