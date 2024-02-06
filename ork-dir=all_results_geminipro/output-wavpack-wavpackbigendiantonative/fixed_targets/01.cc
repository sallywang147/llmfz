#include <fuzzer/FuzzedDataProvider.h>
#include <wavpack/wavpack.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include <wavpack/wavpack.h>
#include <wavpack/wavpack.c>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t data_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const std::string format = stream.ConsumeRemainingBytesAsString();
  std::vector<char> data_buffer(data_size);
  stream.ConsumeBytes(data_buffer.data(), data_size);

  WavpackBigEndianToNative(data_buffer.data(), const_cast<char*>(format.c_str()));
  return 0;
}