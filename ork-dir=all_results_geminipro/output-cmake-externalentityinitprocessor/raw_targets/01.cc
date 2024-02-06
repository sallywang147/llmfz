#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> context_bytes = stream.ConsumeBytes<uint8_t>(
      stream.ConsumeIntegralInRange(0, 100));
  XML_Parser parser = XML_ParserCreate(nullptr);
  XML_SetUserData(parser, context_bytes.data());

  const std::string open_entity_name = stream.ConsumeRemainingBytesAsString();

  int result = externalEntityInitProcessor(parser,
                                          const_cast<char*>(open_entity_name.c_str()),
                                          nullptr, nullptr);
  XML_ParserFree(parser);

  return result;
}