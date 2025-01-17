#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "pb_decode.h"
#include "pb_encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string message_type = stream.ConsumeRemainingBytesAsString();

  const pb_msgdesc_s* fields = pb_find_msgdesc(message_type.c_str());
  if (fields == nullptr) {
    return 0;
  }

  char* src_struct = reinterpret_cast<char*>(
      malloc(pb_msgdesc_sizeof(fields)));
  if (src_struct == nullptr) {
    return 0;
  }

  // Initialize the fields in the message.
  for (int i = 0; i < fields->field_count; i++) {
    const pb_field_iter_t* field = &fields->field[i];
    switch (field->data_size) {
      case 1:
        *reinterpret_cast<uint8_t*>(src_struct + field->data_offset) =
            stream.ConsumeIntegral<uint8_t>();
        break;
      case 2:
        *reinterpret_cast<uint16_t*>(src_struct + field->data_offset) =
            stream.ConsumeIntegral<uint16_t>();
        break;
      case 4:
        *reinterpret_cast<uint32_t*>(src_struct + field->data_offset) =
            stream.ConsumeIntegral<uint32_t>();
        break;
      case 8:
        *reinterpret_cast<uint64_t*>(src_struct + field->data_offset) =
            stream.ConsumeIntegral<uint64_t>();
        break;
      default:
        // TODO(user): Handle other data sizes.
        break;
    }
  }

  // Encode the message.
  pb_ostream_s ostream;
  ostream.callback = nullptr;
  ostream.state = nullptr;
  ostream.max_size = 0;
  ostream.bytes_written = 0;
  ostream.errmsg = nullptr;

  bool success = pb_encode_ex(&ostream, fields, src_struct, 0);
  free(src_struct);

  return success ? 0 : 1;
}