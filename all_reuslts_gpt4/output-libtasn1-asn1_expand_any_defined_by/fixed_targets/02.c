#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "asn1.h"

struct asn1_node_st {
  int type;
  unsigned char *data;
  int data_len;
  struct asn1_node_st *children;
  struct asn1_node_st *next;
  struct asn1_node_st *prev;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  asn1_node_st definitions;
  definitions.type = stream.ConsumeIntegral<int>();
  size_t data_len = stream.ConsumeIntegralInRange<size_t>(0, size / 2);
  std::vector<unsigned char> data_vec = stream.ConsumeBytes<unsigned char>(data_len);
  definitions.data = data_vec.data();
  definitions.data_len = data_len;
  definitions.children = nullptr;
  definitions.next = nullptr;
  definitions.prev = nullptr;

  asn1_node_st element;
  element.type = stream.ConsumeIntegral<int>();
  data_len = stream.ConsumeIntegralInRange<size_t>(0, size / 2);
  data_vec = stream.ConsumeBytes<unsigned char>(data_len);
  element.data = data_vec.data();
  element.data_len = data_len;
  element.children = nullptr;
  element.next = nullptr;
  element.prev = nullptr;

  asn1_node_st* element_ptr = &element;

  asn1_expand_any_defined_by(&definitions, &element_ptr);

  return 0;
}