 #include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

#include "acommon/acommon.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  acommon::PosibErr config;
  acommon::Config filename;
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *in = const_cast<char*>(str.c_str());
  acommon::set_mode_from_extension(&config, &filename, in, 0, nullptr);
  return 0;
}