#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "asn1.h"

struct asn1_node_st {
  int type;
  int element;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(asn1_node_st) * 2) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  asn1_node_st definitions;
  definitions.type = provider.ConsumeIntegral<int>();
  definitions.element = provider.ConsumeIntegral<int>();

  asn1_node_st element;
  element.type = provider.ConsumeIntegral<int>();
  element.element = provider.ConsumeIntegral<int>();

  asn1_node_st* element_ptr = &element;

  asn1_expand_any_defined_by(&definitions, &element_ptr);

  return 0;
}