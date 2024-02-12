 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "acommon.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* filename = stream.ConsumeRemainingBytesAsString().c_str();
  acommon::PosibErr config;
  acommon::Config* config_ptr = &config;
  FILE* file = nullptr;
  acommon::set_mode_from_extension(config_ptr, filename, nullptr, 0, file);
  return 0;
}