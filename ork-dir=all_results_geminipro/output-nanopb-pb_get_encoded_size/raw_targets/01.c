#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "picobench.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string message_type = stream.ConsumeRemainingBytesAsString();
  const struct pb_msgdesc_s *fields = pb_find_msgdesc(message_type.c_str());
  if (fields == nullptr) {
    return 0;
  }

  size_t encoded_size = 0;
  bool success = pb_get_encoded_size(&encoded_size, fields, nullptr);
  if (!success) {
    return 0;
  }

  std::vector<uint8_t> buffer(encoded_size);
  success = pb_encode(fields, nullptr, buffer.data(), buffer.size());
  if (!success) {
    return 0;
  }

  return 0;
}