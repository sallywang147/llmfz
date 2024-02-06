#include <fuzzer/FuzzedDataProvider.h>
#include <protobuf-c/protobuf-c.h>
#include <stdlib.h>

#include <protobuf-c-unpacked.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ProtobufCBuffer buffer;
  protobuf_c_buffer_init(&buffer, 0);

  // Generate a field descriptor.
  ProtobufCFieldDescriptor field;
  field.label = stream.ConsumeIntegralInRange<ProtobufCLabel>(
      PROTOBUF_C_LABEL_OPTIONAL, PROTOBUF_C_LABEL_REPEATED);
  field.type = stream.ConsumeIntegralInRange<ProtobufCType>(
      PROTOBUF_C_TYPE_INT32, PROTOBUF_C_TYPE_STRING);
  field.name = stream.ConsumeRandomLengthString().c_str();

  // Generate a member value.
  char *member;
  size_t member_size;
  switch (field.type) {
    case PROTOBUF_C_TYPE_INT32:
      member_size = sizeof(int32_t);
      member = (char *)malloc(member_size);
      stream.ConsumeIntegral<int32_t>((int32_t *)member);
      break;
    case PROTOBUF_C_TYPE_STRING:
      member_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
      member = (char *)malloc(member_size);
      stream.ConsumeBytes(member, member_size);
      break;
    default:
      // Unhandled type.
      return 0;
  }

  // Pack the field to the buffer.
  size_t packed_size = unlabeled_field_pack_to_buffer(&field, member, &buffer);
  if (packed_size == 0) {
    // Packing failed.
    return 0;
  }

  // Free the member value.
  free(member);

  // Free the buffer.
  protobuf_c_buffer_fini(&buffer);

  return 0;
}