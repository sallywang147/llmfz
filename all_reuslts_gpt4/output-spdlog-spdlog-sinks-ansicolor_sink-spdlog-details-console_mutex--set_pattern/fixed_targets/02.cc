#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "spdlog/sinks/ansicolor_sink.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  auto sink = std::make_shared<spdlog::sinks::ansicolor_sink<spdlog::details::console_mutex>>();
  std::string pattern = stream.ConsumeRandomLengthString();
  
  sink->set_pattern(&pattern);

  return 0;
}