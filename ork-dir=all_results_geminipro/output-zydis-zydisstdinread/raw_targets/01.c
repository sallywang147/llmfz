#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "Zydis/Zydis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t max_len = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> input_buffer = stream.ConsumeBytes<uint8_t>(max_len);
  char* input_buffer_ptr = reinterpret_cast<char*>(input_buffer.data());

  size_t bytes_read = ZydisStdinRead(nullptr, input_buffer_ptr, max_len);
  return 0;
}