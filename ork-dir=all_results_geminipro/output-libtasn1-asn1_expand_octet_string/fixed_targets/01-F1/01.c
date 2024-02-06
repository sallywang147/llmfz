#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "asn1_fuzzer_utils.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct asn1_node_st* definitions = nullptr;
  struct asn1_node_st* element = nullptr;
  char* octetName = nullptr;
  char* objectName = nullptr;

  asn1_fuzzer_init_definitions(&definitions);
  asn1_fuzzer_init_element(&element);
  asn1_fuzzer_init_octetName(&octetName, stream);
  asn1_fuzzer_init_objectName(&objectName, stream);

  int result = asn1_expand_octet_string(definitions, &element, octetName,
                                        objectName);

  asn1_fuzzer_free_definitions(&definitions);
  asn1_fuzzer_free_element(&element);
  asn1_fuzzer_free_octetName(&octetName);
  asn1_fuzzer_free_objectName(&objectName);

  return result;
}