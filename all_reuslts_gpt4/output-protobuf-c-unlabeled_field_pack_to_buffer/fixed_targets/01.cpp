#include <fuzzer/FuzzedDataProvider.h>
#include <protobuf-c/protobuf-c.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the ProtobufCFieldDescriptor
  ProtobufCFieldDescriptor field;
  field.name = stream.ConsumeRandomLengthString().c_str();
  field.id = stream.ConsumeIntegral<uint32_t>();
  field.label = stream.PickValueInArray({PROTOBUF_C_LABEL_OPTIONAL, PROTOBUF_C_LABEL_REQUIRED, PROTOBUF_C_LABEL_REPEATED});
  field.type = stream.PickValueInArray({PROTOBUF_C_TYPE_INT32, PROTOBUF_C_TYPE_SINT32, PROTOBUF_C_TYPE_SFIXED32, PROTOBUF_C_TYPE_INT64, PROTOBUF_C_TYPE_SINT64, PROTOBUF_C_TYPE_SFIXED64, PROTOBUF_C_TYPE_UINT32, PROTOBUF_C_TYPE_FIXED32, PROTOBUF_C_TYPE_UINT64, PROTOBUF_C_TYPE_FIXED64, PROTOBUF_C_TYPE_FLOAT, PROTOBUF_C_TYPE_DOUBLE, PROTOBUF_C_TYPE_BOOL, PROTOBUF_C_TYPE_ENUM, PROTOBUF_C_TYPE_STRING, PROTOBUF_C_TYPE_BYTES, PROTOBUF_C_TYPE_MESSAGE});
  field.quantifier_offset = stream.ConsumeIntegral<size_t>();
  field.offset = stream.ConsumeIntegral<size_t>();
  field.descriptor = nullptr; // We can't easily create a valid descriptor, so we set it to null
  field.default_value = nullptr; // We can't easily create a valid default value, so we set it to null
  field.cdescriptor = nullptr; // We can't easily create a valid cdescriptor, so we set it to null

  // Initialize the ProtobufCBuffer
  ProtobufCBuffer buffer;
  buffer.append = [](ProtobufCBuffer *buffer, size_t len, const uint8_t *data) { return len; }; // Simple append function that just returns the length

  // Initialize the member
  std::string member = stream.ConsumeRandomLengthString();
  
  // Call the target function
  unlabeled_field_pack_to_buffer(&field, const_cast<char*>(member.c_str()), &buffer);

  return 0;
}