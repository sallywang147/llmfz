#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include "asn1_parser2array.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input_file_name = stream.ConsumeRemainingBytesAsString();
  const std::string output_file_name = stream.ConsumeRemainingBytesAsString();
  const std::string vector_name = stream.ConsumeRemainingBytesAsString();
  const std::string error_desc = stream.ConsumeRemainingBytesAsString();

  char* input_file_name_ptr = const_cast<char*>(input_file_name.c_str());
  char* output_file_name_ptr = const_cast<char*>(output_file_name.c_str());
  char* vector_name_ptr = const_cast<char*>(vector_name.c_str());
  char* error_desc_ptr = const_cast<char*>(error_desc.c_str());

  // Fix: Cast the return value of asn1_parser2array to int
  return static_cast<int>(asn1_parser2array(input_file_name_ptr, output_file_name_ptr,
                             vector_name_ptr, error_desc_ptr));
}