#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "spdlog/sinks/ansicolor_sink.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a sink
  auto sink = std::make_shared<spdlog::sinks::ansicolor_sink<spdlog::details::console_mutex>>();

  // Consume data to create a pattern string
  std::string pattern = stream.ConsumeRandomLengthString();

  // Call the target function
  sink->set_pattern(&pattern);

  return 0;
}