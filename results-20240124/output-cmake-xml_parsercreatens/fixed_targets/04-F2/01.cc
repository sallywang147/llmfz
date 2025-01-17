#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libxml/parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t namespace_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto namespace_data = provider.ConsumeBytes<char>(namespace_size);
  const size_t encoding_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto encoding_data = provider.ConsumeBytes<char>(encoding_size);
  struct XML_ParserStruct* parser =
      XML_ParserCreateNS(namespace_data.data(), encoding_data.data()[0]);
  if (parser == nullptr) {
    return 0;
  }
  XML_ParserFree(parser);
  return 0;
}