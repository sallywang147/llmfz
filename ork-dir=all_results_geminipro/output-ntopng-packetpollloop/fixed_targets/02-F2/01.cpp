#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" {
#include "packetPollLoop.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t input_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  const std::vector<uint8_t> input_data = stream.ConsumeBytes<uint8_t>(input_size);
  char* input_ptr = reinterpret_cast<char*>(input_data.data());
  char* output_ptr = packetPollLoop(input_ptr);
  free(output_ptr);
  return 0;
}