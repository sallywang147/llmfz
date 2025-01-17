#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "protobuf-c/protobuf-c.h"

struct SimpleBuffer : public ProtobufCBuffer {
  std::vector<uint8_t> data;

  static void append(ProtobufCBuffer* buffer, size_t len, const uint8_t* data) {
    auto* simple_buffer = static_cast<SimpleBuffer*>(buffer);
    simple_buffer->data.insert(simple_buffer->data.end(), data, data + len);
  }
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the field descriptor.
  ProtobufCFieldDescriptor field;
  field.name = "fuzz_field";
  field.id = stream.ConsumeIntegral<uint32_t>();
  field.label = stream.PickValueInArray(
      {PROTOBUF_C_LABEL_OPTIONAL, PROTOBUF_C_LABEL_REQUIRED, PROTOBUF_C_LABEL_REPEATED});
  field.type = stream.PickValueInArray(
      {PROTOBUF_C_TYPE_INT32, PROTOBUF_C_TYPE_SINT32, PROTOBUF_C_TYPE_SFIXED32,
       PROTOBUF_C_TYPE_INT64, PROTOBUF_C_TYPE_SINT64, PROTOBUF_C_TYPE_SFIXED64,
       PROTOBUF_C_TYPE_UINT32, PROTOBUF_C_TYPE_FIXED32, PROTOBUF_C_TYPE_UINT64,
       PROTOBUF_C_TYPE_FIXED64, PROTOBUF_C_TYPE_FLOAT, PROTOBUF_C_TYPE_DOUBLE,
       PROTOBUF_C_TYPE_BOOL, PROTOBUF_C_TYPE_ENUM, PROTOBUF_C_TYPE_STRING,
       PROTOBUF_C_TYPE_BYTES, PROTOBUF_C_TYPE_MESSAGE});
  field.quantifier_offset = 0;
  field.offset = 0;
  field.descriptor = nullptr;
  field.flags = 0;
  field.default_value = nullptr;

  // Initialize the buffer.
  SimpleBuffer buffer;
  buffer.append = SimpleBuffer::append;

  // Initialize the member.
  std::string member = stream.ConsumeRandomLengthString();

  // Call the function under test.
  optional_field_pack_to_buffer(&field, stream.ConsumeBool(), const_cast<char*>(member.c_str()), &buffer);

  return 0;
}