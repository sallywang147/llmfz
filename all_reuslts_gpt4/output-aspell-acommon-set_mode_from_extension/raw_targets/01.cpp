#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "acommon.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  acommon::PosibErr config;
  acommon::Config filename;
  int randomInt = stream.ConsumeIntegral<int>();
  struct _IO_FILE file;

  std::string str = stream.ConsumeRemainingBytesAsString();
  char *in = const_cast<char*>(str.c_str());

  acommon::set_mode_from_extension(&config, &filename, in, randomInt, &file);

  return 0;
}