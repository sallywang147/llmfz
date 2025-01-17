#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pb.h"
#include "pb_encode.h"
#include "pb_decode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Define and initialize variables
  size_t encoded_size = 0;
  pb_msgdesc_s fields;
  std::vector<char> src_struct_vector = stream.ConsumeBytes<char>(stream.remaining_bytes());
  char* src_struct = src_struct_vector.data();

  // Call the target function
  bool result = pb_get_encoded_size(&encoded_size, &fields, src_struct);

  return 0;
}