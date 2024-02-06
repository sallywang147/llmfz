#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "asn1.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  asn1_node_st definitions;
  asn1_node_st* element = nullptr;

  // We need to ensure that the strings are null-terminated.
  std::string octetName = provider.ConsumeBytesAsString(provider.remaining_bytes() / 2);
  std::string objectName = provider.ConsumeRemainingBytesAsString();

  asn1_expand_octet_string(&definitions, &element, const_cast<char*>(octetName.c_str()), const_cast<char*>(objectName.c_str()));

  return 0;
}