#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "acommon/acommon.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  acommon::PosibErr config;
  acommon::Config filename;
  const std::string input = stream.ConsumeRemainingBytesAsString();
  set_mode_from_extension(&config, &filename, const_cast<char*>(input.c_str()), 0,
                          nullptr);
  return 0;
}