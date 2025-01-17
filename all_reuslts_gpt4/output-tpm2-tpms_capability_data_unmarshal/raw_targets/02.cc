#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "TPMS_CAPABILITY_DATA.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct TPMS_CAPABILITY_DATA target;
  std::string buffer_str = stream.ConsumeRemainingBytesAsString();
  char* buffer = const_cast<char*>(buffer_str.c_str());
  int buffer_size = buffer_str.size();

  TPMS_CAPABILITY_DATA_Unmarshal(&target, &buffer, &buffer_size);

  return 0;
}