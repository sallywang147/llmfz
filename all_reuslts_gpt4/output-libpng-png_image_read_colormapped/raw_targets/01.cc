#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::string str = stream.ConsumeRandomLengthString();
  char *arg = const_cast<char*>(str.c_str());
  
  png_image_read_colormapped(arg);
  
  return 0;
}