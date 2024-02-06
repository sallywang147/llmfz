#include <fuzzer/FuzzedDataProvider.h>
#include <freetype/freetype.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "freetype/gzip.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string text = stream.ConsumeRemainingBytesAsString();
  freetype::GzipFuzzTarget target(text.c_str(), text.size());
  return 0;
}