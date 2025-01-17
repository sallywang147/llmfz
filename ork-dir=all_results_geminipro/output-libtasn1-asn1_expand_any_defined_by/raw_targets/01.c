#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include <asn1_fuzzer_utils.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<struct asn1_node_st*> definitions;
  while (stream.remaining_bytes() > 0) {
    definitions.push_back(asn1_fuzzer_consume_asn1_node(&stream));
  }

  struct asn1_node_st* element = nullptr;
  int ret = asn1_expand_any_defined_by(definitions.data(), &element);
  if (ret == 0) {
    asn1_fuzzer_free_asn1_node(element);
  }
  for (auto* node : definitions) {
    asn1_fuzzer_free_asn1_node(node);
  }
  return 0;
}