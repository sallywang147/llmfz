#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "EncoderCore.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an instance of EncoderCore
  EncoderCore<short, true> encoder;

  // Extract a string from the stream
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = const_cast<char*>(str.c_str());

  // Extract a size_t value from the stream
  size_t sz = stream.ConsumeIntegral<size_t>();

  // Extract a boolean value from the stream
  bool b = stream.ConsumeBool();

  // Call the Run function
  encoder.Run(&encoder, ptr, sz, b);

  return 0;
}