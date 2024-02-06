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

  // Initialize the XML encoding structure
  struct encoding enc;
  enc.scanner = nullptr;

  FuzzedDataProvider stream(data, size);

  // Consume a string for ptr
  std::string str = stream.ConsumeRandomLengthString();
  char* ptr = const_cast<char*>(str.c_str());

  // The end pointer should be after the ptr in memory
  char* end = ptr + str.size();

  // Initialize the nextTokPtr
  char* nextTokPtr = nullptr;

  // Call the function with the fuzzed inputs
  int result = initScanContentNS(&enc, ptr, end, &nextTokPtr);

  return 0;
}