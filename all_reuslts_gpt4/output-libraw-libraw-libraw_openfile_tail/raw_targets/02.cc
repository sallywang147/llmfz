#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <libraw/libraw.h>
#include <exception>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize LibRaw instance
  LibRaw rawProcessor;
  
  // Create an exception object
  std::exception e;
  
  // Call the function to be fuzzed
  rawProcessor.libraw_openfile_tail(&rawProcessor, &e);

  return 0;
}