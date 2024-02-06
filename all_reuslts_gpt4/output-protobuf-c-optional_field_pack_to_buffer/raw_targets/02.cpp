#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "protobuf-c/protobuf-c.h"

struct SimpleBuffer {
  std::vector<uint8_t> data;
};

static void simple_buffer_append(ProtobufCBuffer* buffer,
                                 size_t len,
                                 const uint8_t* data) {
  SimpleBuffer* simple_buffer = reinterpret_cast<SimpleBuffer*>(buffer);
  simple_buffer->data.insert(simple_buffer->data.end(), data, data + len);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize a ProtobufCFieldDescriptor.
  ProtobufCFieldDescriptor field;
  field.name = "fuzzed_field";
  field.id = stream.ConsumeIntegral<uint32_t>();
  field.label = static_cast<ProtobufCLabel>(stream.ConsumeIntegralInRange<int>(PROTOBUF_C_LABEL_REQUIRED, PROTOBUF_C_LABEL_REPEATED));
  field.type = static_cast<ProtobufCType>(stream.ConsumeIntegralInRange<int>(PROTOBUF_C_TYPE_INT32, PROTOBUF_C_TYPE_MESSAGE));
  field.quantifier_offset = stream.ConsumeIntegral<uint32_t>();
  field.offset = stream.ConsumeIntegral<uint32_t>();
  field.descriptor = nullptr;
  field.flags = stream.ConsumeIntegral<uint32_t>();
  field.reserved2 = stream.ConsumeIntegral<uint32_t>();
  field.reserved3 = stream.ConsumeIntegral<uint32_t>();

  // Initialize a ProtobufCBuffer.
  SimpleBuffer simple_buffer;
  ProtobufCBuffer buffer;
  buffer.append = simple_buffer_append;

  // Initialize member.
  std::string member = stream.ConsumeRandomLengthString();
  
  // Initialize has.
  int has = stream.ConsumeBool();

  // Call the target function.
  optional_field_pack_to_buffer(&field, has, const_cast<char*>(member.c_str()), &buffer);

  return 0;
}