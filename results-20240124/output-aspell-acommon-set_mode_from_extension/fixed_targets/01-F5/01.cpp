#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "acommon.h"

extern "C" {
#include "acommon_fuzzer.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  char *filename_ptr = const_cast<char*>(filename.c_str());
  acommon::PosibErr config;
  acommon::Config config_filename;
  acommon::set_mode_from_extension(&config, &config_filename, filename_ptr, 0, nullptr);
  return 0;
}