 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include "acommon.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string filename = stream.ConsumeRemainingBytesAsString();

  acommon::PosibErr config;
  acommon::Config config_filename;
  config_filename.set_name(filename.c_str());

  acommon::set_mode_from_extension(&config, &config_filename, nullptr, 0, nullptr);
  return 0;
}