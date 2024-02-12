 #include <fuzzer/FuzzedDataProvider.h>
#include <freetype/ftlzw.h>
#include <freetype/fttypes.h>
#include <iostream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::vector<uint8_t> bytes(data, data + size);
  freetype::LzwFuzzTarget target(bytes);
  target.LzwFuzzTarget(&target);
  return 0;
}