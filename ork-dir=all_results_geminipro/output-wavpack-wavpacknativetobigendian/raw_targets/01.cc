#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t data_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const std::string format = stream.ConsumeRemainingBytesAsString();
  std::vector<char> data_vector(data_size);
  stream.ConsumeBytes<char>(data_vector.data(), data_size);
  WavpackNativeToBigEndian(data_vector.data(), const_cast<char*>(format.c_str()));
  return 0;
}