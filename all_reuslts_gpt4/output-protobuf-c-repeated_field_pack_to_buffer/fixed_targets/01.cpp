#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "protobuf-c/protobuf-c.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize ProtobufCFieldDescriptor
  ProtobufCFieldDescriptor field;
  field.name = provider.ConsumeRandomLengthString().c_str();
  field.id = provider.ConsumeIntegral<uint32_t>();
  field.label = provider.PickValueInArray({PROTOBUF_C_LABEL_REQUIRED, PROTOBUF_C_LABEL_OPTIONAL, PROTOBUF_C_LABEL_REPEATED});
  field.type = provider.PickValueInArray({PROTOBUF_C_TYPE_INT32, PROTOBUF_C_TYPE_SINT32, PROTOBUF_C_TYPE_SFIXED32, PROTOBUF_C_TYPE_INT64, PROTOBUF_C_TYPE_SINT64, PROTOBUF_C_TYPE_SFIXED64, PROTOBUF_C_TYPE_UINT32, PROTOBUF_C_TYPE_FIXED32, PROTOBUF_C_TYPE_UINT64, PROTOBUF_C_TYPE_FIXED64, PROTOBUF_C_TYPE_FLOAT, PROTOBUF_C_TYPE_DOUBLE, PROTOBUF_C_TYPE_BOOL, PROTOBUF_C_TYPE_ENUM, PROTOBUF_C_TYPE_STRING, PROTOBUF_C_TYPE_BYTES, PROTOBUF_C_TYPE_MESSAGE});
  field.quantifier_offset = provider.ConsumeIntegral<uint32_t>();
  field.offset = provider.ConsumeIntegral<uint32_t>();
  field.descriptor = NULL; // For simplicity, we'll not use sub-messages

  // Initialize count
  int count = provider.ConsumeIntegral<int>();

  // Initialize member
  std::string member = provider.ConsumeRandomLengthString();
  
  // Initialize ProtobufCBuffer
  ProtobufCBuffer buffer;
  buffer.append = NULL; // For simplicity, we'll not append any data to the buffer

  // Call the function
  size_t result = repeated_field_pack_to_buffer(&field, count, const_cast<char*>(member.c_str()), &buffer);

  return 0;
}