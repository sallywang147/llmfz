#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "asn1.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the source and destination asn1_node_st objects
  struct asn1_node_st src, dst;

  // Consume data for the source and destination node names
  std::string src_name = stream.ConsumeRandomLengthString();
  std::string dst_name = stream.ConsumeRandomLengthString();

  // Call the function to be fuzzed
  asn1_copy_node(&dst, const_cast<char*>(dst_name.c_str()), &src, const_cast<char*>(src_name.c_str()));

  return 0;
}