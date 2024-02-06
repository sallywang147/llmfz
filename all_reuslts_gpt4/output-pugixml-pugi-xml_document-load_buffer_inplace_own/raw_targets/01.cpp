#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "pugixml.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  size_t options = stream.ConsumeIntegral<size_t>();
  int encoding = stream.ConsumeIntegral<int>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *buffer = const_cast<char *>(str.c_str());

  // Create xml_document and xml_parse_result objects
  pugi::xml_document doc;
  pugi::xml_parse_result result;

  // Call the target function
  doc.load_buffer_inplace_own(&result, &doc, buffer, options, encoding, 0);

  return 0;
}