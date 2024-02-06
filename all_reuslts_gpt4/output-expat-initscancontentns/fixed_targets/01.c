#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "xmltok.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize encoding structure
  struct encoding enc;
  enc.scanners[XML_CONTENT_STATE] = NULL;
  enc.scanners[XML_PROLOG_STATE] = NULL;
  enc.updatePosition = NULL;
  enc.encPtr = NULL;
  enc.minBytesPerChar = stream.ConsumeIntegral<unsigned int>();
  enc.isUtf16 = stream.ConsumeBool();
  enc.isUtf8 = stream.ConsumeBool();

  // Consume data for ptr and end
  size_t remaining_bytes_half = stream.remaining_bytes() / 2;
  std::string ptr_str = stream.ConsumeBytesAsString(remaining_bytes_half);
  std::string end_str = stream.ConsumeBytesAsString(remaining_bytes_half);

  // Initialize ptr and end
  char* ptr = const_cast<char*>(ptr_str.c_str());
  char* end = const_cast<char*>(end_str.c_str());

  // Initialize nextTokPtr
  char* nextTokPtr = NULL;

  // Call the target function
  initScanContentNS(&enc, ptr, end, &nextTokPtr);

  return 0;
}