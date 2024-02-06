#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string argument = stream.ConsumeRandomLengthString();
  
  png_image_read_colormapped(const_cast<char*>(argument.c_str()));

  return 0;
}