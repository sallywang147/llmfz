#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "acommon.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  acommon::PosibErr config;
  acommon::Config filename;
  const int length = stream.ConsumeIntegral<int>();
  char* in = new char[length];
  stream.ConsumeBytes(in, length);
  acommon::set_mode_from_extension(&config, &filename, in, length, nullptr);
  delete[] in;

  return 0;
}