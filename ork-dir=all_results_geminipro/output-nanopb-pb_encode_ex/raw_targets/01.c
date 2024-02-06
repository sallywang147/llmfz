#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

#include "pb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string message_name = stream.ConsumeRemainingBytesAsString();
  const pb_msgdesc_s* message_desc = pb_find_msgdesc(message_name.c_str());
  if (message_desc == nullptr) {
    return 0;
  }
  const size_t message_size = pb_msgdesc_sizeof(message_desc);
  std::vector<uint8_t> message(message_size);
  if (!pb_encode_ex(nullptr, message_desc, message.data(), 0)) {
    return 0;
  }
  return 0;
}