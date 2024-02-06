#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pb_encode.h"
#include "pb_decode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for pb_encode_ex function
  pb_ostream_s pb_stream = pb_ostream_from_buffer(nullptr, 0);
  pb_msgdesc_s fields = {0};
  char src_struct[100] = {0};
  int flags = stream.ConsumeIntegral<int>();

  // Consume some data for the fields and src_struct
  size_t fields_data_size = stream.ConsumeIntegralInRange<size_t>(0, 50);
  auto fields_data = stream.ConsumeBytes<uint8_t>(fields_data_size);
  memcpy(&fields, fields_data.data(), fields_data_size);

  size_t src_struct_data_size = stream.ConsumeIntegralInRange<size_t>(0, 50);
  auto src_struct_data = stream.ConsumeBytes<uint8_t>(src_struct_data_size);
  memcpy(&src_struct, src_struct_data.data(), src_struct_data_size);

  // Call the function to fuzz
  pb_encode_ex(&pb_stream, &fields, src_struct, flags);

  return 0;
}