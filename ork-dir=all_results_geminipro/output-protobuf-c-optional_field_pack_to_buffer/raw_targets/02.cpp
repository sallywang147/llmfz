#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "protobuf-c.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a fake field descriptor.
  ProtobufCFieldDescriptor field;
  field.name = stream.ConsumeRandomLengthString().c_str();
  field.type = stream.ConsumeIntegralInRange<ProtobufCType>(
      PROTOBUF_C_TYPE_INT32, PROTOBUF_C_TYPE_DOUBLE);
  field.label = stream.ConsumeIntegralInRange<ProtobufCLabel>(
      PROTOBUF_C_LABEL_OPTIONAL, PROTOBUF_C_LABEL_REPEATED);
  field.offset = stream.ConsumeIntegral<int32_t>();

  // Create a fake buffer.
  ProtobufCBuffer buffer;
  buffer.len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  buffer.data = static_cast<uint8_t*>(malloc(buffer.len));

  // Create a fake member.
  char* member = static_cast<char*>(malloc(1024));
  size_t member_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  stream.ConsumeBytes<uint8_t>(member, member_size);

  // Call the function.
  size_t result = optional_field_pack_to_buffer(&field, 1, member, &buffer);

  // Free the allocated memory.
  free(buffer.data);
  free(member);

  return 0;
}