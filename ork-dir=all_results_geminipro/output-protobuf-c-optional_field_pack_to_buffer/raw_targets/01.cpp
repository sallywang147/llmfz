#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "protobuf-c.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct ProtobufCBuffer buffer;
  protobuf_c_buffer_init(&buffer, 0, NULL);

  // Initialize a field descriptor.
  struct ProtobufCFieldDescriptor field;
  memset(&field, 0, sizeof(field));
  field.label = PROTOBUF_C_LABEL_OPTIONAL;
  field.type = PROTOBUF_C_TYPE_INT32;
  field.name = (char*)"test_field";

  // Initialize a member variable.
  int32_t member = 0;

  // Call the function to be fuzzed.
  size_t packed_size = optional_field_pack_to_buffer(&field, 1, (char*)&member, &buffer);

  // Free the buffer.
  protobuf_c_buffer_fini(&buffer);

  // Return 0 to indicate successful execution.
  return 0;
}