#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int png_image_read_direct(char * argument);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str_arg = stream.ConsumeRemainingBytesAsString();
  char* char_ptr = const_cast<char*>(str_arg.c_str());

  png_image_read_direct(char_ptr);

  return 0;
}