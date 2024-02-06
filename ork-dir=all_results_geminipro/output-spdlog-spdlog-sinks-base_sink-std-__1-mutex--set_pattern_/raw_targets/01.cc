#include <cstddef>
#include <fuzzer/FuzzedDataProvider.h>
#include <string>

#include "spdlog/sinks/base_sink.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  spdlog::sinks::base_sink<std::mutex> sink;
  std::string pattern = stream.ConsumeRandomLengthString();
  sink.set_pattern_(&sink, &pattern);

  return 0;
}