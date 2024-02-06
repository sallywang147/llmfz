#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "yajl/yajl_gen.h"

extern "C" {
  int yajl_string_encode(yajl_buf* buf, const char* string, size_t len,
                         int htmlSafe);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t max_string_size = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  const size_t string_size = provider.ConsumeIntegralInRange<size_t>(0, max_string_size);
  std::vector<uint8_t> string_data = provider.ConsumeBytes<uint8_t>(string_size);
  char* string = reinterpret_cast<char*>(string_data.data());

  const size_t max_buffer_size = provider.ConsumeIntegralInRange<size_t>(1, 10000);
  const size_t buffer_size = provider.ConsumeIntegralInRange<size_t>(0, max_buffer_size);
  std::vector<uint8_t> buffer_data(buffer_size);
  yajl_buf buf = {buffer_data.data(), buffer_size, 0};

  const bool htmlSafe = provider.ConsumeBool();

  yajl_string_encode(&buf, string, strlen(string), htmlSafe);

  return 0;
}