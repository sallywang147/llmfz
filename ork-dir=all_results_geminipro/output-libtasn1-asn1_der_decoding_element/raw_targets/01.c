#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "asn1_der.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t structure_size = stream.ConsumeIntegralInRange<size_t>(1, 100);
  struct asn1_node_st* structure =
      static_cast<struct asn1_node_st*>(malloc(structure_size));
  if (structure == nullptr) {
    return 0;
  }
  memset(structure, 0, structure_size);

  const size_t element_name_size =
      stream.ConsumeIntegralInRange<size_t>(1, 100);
  char* element_name =
      static_cast<char*>(malloc(element_name_size));
  if (element_name == nullptr) {
    free(structure);
    return 0;
  }
  stream.ConsumeBytes<char>(element_name, element_name_size);

  const size_t ider_size = stream.ConsumeIntegralInRange<size_t>(1, 100);
  char* ider = static_cast<char*>(malloc(ider_size));
  if (ider == nullptr) {
    free(structure);
    free(element_name);
    return 0;
  }
  stream.ConsumeBytes<char>(ider, ider_size);

  const size_t len = stream.ConsumeIntegralInRange<size_t>(1, 100);

  const size_t error_description_size =
      stream.ConsumeIntegralInRange<size_t>(1, 100);
  char* error_description =
      static_cast<char*>(malloc(error_description_size));
  if (error_description == nullptr) {
    free(structure);
    free(element_name);
    free(ider);
    return 0;
  }
  stream.ConsumeBytes<char>(error_description, error_description_size);

  asn1_der_decoding_element(&structure, element_name, ider, len,
                            error_description);

  free(structure);
  free(element_name);
  free(ider);
  free(error_description);

  return 0;
}