#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "freetype/freetype.h"

#include "freetype/lzwfuzztarget.h"

extern "C" {
#include "freetype/lzw.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string text = stream.ConsumeRemainingBytesAsString();
  freetype::LzwFuzzTarget target(text);
  return 0;
}