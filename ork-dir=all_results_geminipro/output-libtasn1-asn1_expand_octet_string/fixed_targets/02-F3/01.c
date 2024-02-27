#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include <asn1c/asn1c.h>
#include <asn1c/asn1_common.h>
#include <asn1c/asn1_codec.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t definitions_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> definitions_bytes =
      stream.ConsumeBytes<uint8_t>(definitions_size);
  char* definitions = reinterpret_cast<char*>(definitions_bytes.data());

  const size_t element_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> element_bytes =
      stream.ConsumeBytes<uint8_t>(element_size);
  char* element = reinterpret_cast<char*>(element_bytes.data());

  const size_t octetName_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> octetName_bytes =
      stream.ConsumeBytes<uint8_t>(octetName_size);
  char* octetName = reinterpret_cast<char*>(octetName_bytes.data());

  const size_t objectName_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> objectName_bytes =
      stream.ConsumeBytes<uint8_t>(objectName_size);
  char* objectName = reinterpret_cast<char*>(objectName_bytes.data());

  asn1_node_st* definitions_node = NULL;
  asn1_node_st* element_node = NULL;
  asn1_expand_octet_string(
      definitions_node, &element_node, octetName, objectName);
  return 0;
}