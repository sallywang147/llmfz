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

  // Create a buffer for the src_struct
  std::vector<char> src_struct_buffer = stream.ConsumeBytes<char>(stream.remaining_bytes() / 2);
  char* src_struct = src_struct_buffer.data();

  // Create a buffer for the fields
  std::vector<pb_msgdesc_s> fields_buffer = stream.ConsumeRemainingBytes<pb_msgdesc_s>();
  pb_msgdesc_s* fields = fields_buffer.data();

  // Initialize size variable
  size_t encoded_size = 0;

  // Call the function to fuzz
  pb_get_encoded_size(&encoded_size, fields, src_struct);

  return 0;
}