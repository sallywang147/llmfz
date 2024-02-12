#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "acommon.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  acommon::PosibErr config;
  std::string filename_str = stream.ConsumeRemainingBytesAsString();
  acommon::Config filename(filename_str.c_str());
  acommon::set_mode_from_extension(&config, &filename, nullptr, 0, nullptr);
  return 0;
}