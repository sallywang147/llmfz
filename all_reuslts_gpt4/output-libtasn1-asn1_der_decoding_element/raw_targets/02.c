#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libtasn1.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct asn1_node_st* structure = nullptr;
  char errorDescription[ASN1_MAX_ERROR_DESCRIPTION_SIZE];
  
  // Consume some data for elementName and ider
  std::string elementName = stream.ConsumeRandomLengthString();
  std::vector<char> ider = stream.ConsumeRemainingBytes<char>();

  int len = ider.size();

  int result = asn1_der_decoding_element(&structure, const_cast<char*>(elementName.c_str()), ider.data(), len, errorDescription);
  
  // Free the allocated structure
  if (structure != nullptr) {
    asn1_delete_structure(&structure);
  }

  return 0;
}