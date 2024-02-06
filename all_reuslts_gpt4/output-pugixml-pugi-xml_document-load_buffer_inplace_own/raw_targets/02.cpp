#include <fuzzer/FuzzedDataProvider.h>
#include <pugixml.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  pugi::xml_document doc;
  pugi::xml_parse_result result;
  pugi::xml_parse_status status = static_cast<pugi::xml_parse_status>(stream.ConsumeIntegralInRange<int>(0, 9));
  pugi::xml_encoding encoding = static_cast<pugi::xml_encoding>(stream.ConsumeIntegralInRange<int>(0, 2));
  size_t options = stream.ConsumeIntegral<size_t>();
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *buffer = const_cast<char *>(str.c_str());

  result.status = status;
  result.offset = 0;
  result.encoding = encoding;

  doc.load_buffer_inplace_own(&result, buffer, options, encoding);

  return 0;
}