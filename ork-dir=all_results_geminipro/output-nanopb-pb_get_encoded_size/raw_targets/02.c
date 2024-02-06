#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "pb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string message_name = stream.ConsumeRemainingBytesAsString();
  const struct pb_msgdesc_s* fields = pb_find_msgdesc(message_name.c_str());
  if (fields == nullptr) {
    return 0;
  }
  std::vector<uint8_t> bytes(stream.ConsumeIntegralInRange(0, size));
  char* src_struct = reinterpret_cast<char*>(bytes.data());
  size_t size_out;
  bool result = pb_get_encoded_size(&size_out, fields, src_struct);
  if (result) {
    std::vector<uint8_t> output_buffer(size_out);
    pb_encode_ex(fields, reinterpret_cast<const void*>(src_struct),
                 output_buffer.data(), output_buffer.size(), NULL, 0, NULL);
  }
  return 0;
}