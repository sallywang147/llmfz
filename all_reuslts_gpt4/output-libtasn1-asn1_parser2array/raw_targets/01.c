#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Divide the input data into four parts for four parameters of the function
  size_t quarter_size = size / 4;

  std::string inputFileName = stream.ConsumeBytesAsString(quarter_size);
  std::string outputFileName = stream.ConsumeBytesAsString(quarter_size);
  std::string vectorName = stream.ConsumeBytesAsString(quarter_size);
  std::string error_desc = stream.ConsumeRemainingBytesAsString();

  // Call the target function
  asn1_parser2array(const_cast<char*>(inputFileName.c_str()), 
                    const_cast<char*>(outputFileName.c_str()), 
                    const_cast<char*>(vectorName.c_str()), 
                    const_cast<char*>(error_desc.c_str()));

  return 0;
}