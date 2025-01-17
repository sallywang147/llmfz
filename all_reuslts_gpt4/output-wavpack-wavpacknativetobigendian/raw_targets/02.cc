#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "wavpack.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume a string from the stream for the 'data' parameter
  std::string data_str = stream.ConsumeRandomLengthString();
  char *data_ptr = const_cast<char *>(data_str.c_str());

  // Consume a string from the stream for the 'format' parameter
  std::string format_str = stream.ConsumeRandomLengthString();
  char *format_ptr = const_cast<char *>(format_str.c_str());

  // Call the function under test
  WavpackNativeToBigEndian(data_ptr, format_ptr);

  return 0;
}