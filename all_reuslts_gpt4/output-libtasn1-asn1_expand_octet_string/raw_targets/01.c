#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "asn1.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct asn1_node_st definitions;
  struct asn1_node_st* element = nullptr;
  
  size_t octetNameSize = stream.ConsumeIntegralInRange<size_t>(0, size / 2);
  std::string octetName = stream.ConsumeBytesAsString(octetNameSize);
  std::string objectName = stream.ConsumeRemainingBytesAsString();

  asn1_expand_octet_string(&definitions, &element, const_cast<char*>(octetName.c_str()), const_cast<char*>(objectName.c_str()));

  return 0;
}