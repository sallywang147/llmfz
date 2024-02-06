#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pugixml.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  pugi::xml_document doc;
  pugi::xml_parse_result result;
  pugi::xml_encoding encoding = stream.ConsumeEnum<pugi::xml_encoding>();
  unsigned int options = stream.ConsumeIntegral<unsigned int>();

  std::string buffer = stream.ConsumeRemainingBytesAsString();
  char* buffer_ptr = const_cast<char*>(buffer.c_str());

  doc.load_buffer_inplace(buffer_ptr, buffer.size(), options, encoding);

  return 0;
}