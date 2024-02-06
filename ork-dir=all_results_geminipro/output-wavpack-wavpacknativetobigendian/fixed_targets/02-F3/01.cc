#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "wavpack.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string format = stream.ConsumeRemainingBytesAsString();
  std::string data_str = stream.ConsumeRemainingBytesAsString();

  extern "C" {
    WavpackNativeToBigEndian(data_str.data(), const_cast<char*>(format.c_str()));
  }
  return 0;
}