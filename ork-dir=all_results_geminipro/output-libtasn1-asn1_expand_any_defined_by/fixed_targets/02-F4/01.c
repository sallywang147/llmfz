#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <asn1_fuzz.h>
#include <asn1_gen.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t num_nodes = stream.ConsumeIntegral<size_t>();
  struct asn1_node_st** nodes = new struct asn1_node_st*[num_nodes];
  for (size_t i = 0; i < num_nodes; i++) {
    nodes[i] = asn1_fuzz_node_value(stream);
  }
  struct asn1_node_st* element = nullptr;
  int ret = asn1_expand_any_defined_by(nodes[0], &element);
  asn1_fuzz_node_free(element); // Free the allocated memory for `element`.
  for (size_t i = 0; i < num_nodes; i++) {
    asn1_fuzz_node_free(nodes[i]);
  }
  delete[] nodes;
  return ret;
}