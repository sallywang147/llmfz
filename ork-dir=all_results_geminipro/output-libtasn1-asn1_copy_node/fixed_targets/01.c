#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "asn1_fuzz.h"
#include "asn1_parser.h"

extern "C" {
#include "asn1_copy.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct asn1_node_st *dst = asn1_create_node();
  struct asn1_node_st *src = asn1_create_node();

  const std::string dst_name = stream.ConsumeRemainingBytesAsString();
  const std::string src_name = stream.ConsumeRemainingBytesAsString();

  asn1_copy_node(dst, const_cast<char*>(dst_name.c_str()), src,
                 const_cast<char*>(src_name.c_str()), NULL, NULL);

  asn1_delete_node(dst);
  asn1_delete_node(src);

  return 0;
}