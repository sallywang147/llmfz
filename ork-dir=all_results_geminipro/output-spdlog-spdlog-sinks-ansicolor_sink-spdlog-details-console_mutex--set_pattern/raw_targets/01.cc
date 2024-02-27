#include <cstddef>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "spdlog/sinks/ansicolor_sink.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string pattern = stream.ConsumeRandomLengthString();

  spdlog::sinks::ansicolor_sink<spdlog::details::console_mutex> sink;
  sink.set_pattern(&sink, &pattern);

  return 0;
}