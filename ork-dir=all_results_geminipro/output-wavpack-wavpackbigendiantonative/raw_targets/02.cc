#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(0, 100000);
  const size_t format_size = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  char* buffer = new char[buffer_size];
  char* format = new char[format_size];
  stream.ConsumeBytes(buffer, buffer_size);
  stream.ConsumeBytes(format, format_size);
  WavpackBigEndianToNative(buffer, format);
  delete[] buffer;
  delete[] format;
  return 0;
}