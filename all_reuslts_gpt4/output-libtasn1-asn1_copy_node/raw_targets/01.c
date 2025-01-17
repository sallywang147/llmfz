#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include "asn1.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct asn1_node_st dst;
  struct asn1_node_st src;

  // Consume data for source and destination names
  std::string src_name = stream.ConsumeRandomLengthString();
  std::string dst_name = stream.ConsumeRandomLengthString();

  // Call the function under test
  asn1_copy_node(&dst, const_cast<char*>(dst_name.c_str()), &src, const_cast<char*>(src_name.c_str()));

  return 0;
}