#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <vector>

#include "libtasn1.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for asn1_der_decoding_element function
  asn1_node_st* structure = nullptr;
  const size_t elementNameLen = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes()/3);
  std::string elementName = stream.ConsumeBytesAsString(elementNameLen);
  const size_t iderLen = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes()/2);
  std::string ider = stream.ConsumeBytesAsString(iderLen);
  int len = ider.size();
  char errorDescription[ASN1_MAX_ERROR_DESCRIPTION_SIZE];

  // Call the target function
  asn1_der_decoding_element(&structure, const_cast<char*>(elementName.c_str()), const_cast<char*>(ider.c_str()), len, errorDescription);

  // Clean up
  if (structure) {
    asn1_delete_structure(&structure);
  }

  return 0;
}