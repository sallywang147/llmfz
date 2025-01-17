 #include <fuzzer/FuzzedDataProvider.h>
#include <freetype/freetype.h>
#include <freetype/ftgzip.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  freetype::GzipFuzzTarget target;
  target.GzipFuzzTarget(&target);
  return 0;
}