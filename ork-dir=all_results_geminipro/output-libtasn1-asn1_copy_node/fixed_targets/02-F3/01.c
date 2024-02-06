#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <string>

#include "asn1.h"

extern "C" {
#include "asn1_internal.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct asn1_node_st* dst = asn1_create_node();
  if (dst == nullptr) {
    return 0;
  }
  const std::string dst_name = stream.ConsumeRemainingBytesAsString();
  struct asn1_node_st* src = asn1_create_node();
  if (src == nullptr) {
    asn1_delete_node(dst);
    return 0;
  }
  const std::string src_name = stream.ConsumeRemainingBytesAsString();
  int ret = asn1_copy_node(dst, dst_name.c_str(), src, src_name.c_str());
  asn1_delete_node(dst);
  asn1_delete_node(src);
  return ret;
}