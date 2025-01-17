#include <fuzzer/FuzzedDataProvider.h>
#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string encoding = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  char namespaceSeparator = stream.ConsumeIntegral<char>();

  XML_Parser parser = XML_ParserCreateNS(encoding.empty() ? NULL : encoding.c_str(), namespaceSeparator);
  if (parser) {
    XML_ParserFree(parser);
  }

  return 0;
}