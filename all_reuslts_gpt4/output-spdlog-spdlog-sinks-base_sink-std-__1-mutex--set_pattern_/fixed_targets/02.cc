#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "spdlog/sinks/base_sink.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string pattern = stream.ConsumeRandomLengthString();
  spdlog::sinks::base_sink<std::__1::mutex> sink;

  spdlog::sinks::base_sink<std::__1::mutex>::set_pattern_(&sink, &pattern);

  return 0;
}