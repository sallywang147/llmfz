#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "protobuf-c/protobuf-c.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a ProtobufCFieldDescriptor
  ProtobufCFieldDescriptor field;
  field.name = stream.ConsumeRandomLengthString().c_str();
  field.id = stream.ConsumeIntegral<uint32_t>();
  field.label = stream.ConsumeEnum<ProtobufCLabel>();
  field.type = stream.ConsumeEnum<ProtobufCType>();
  field.quantifier_offset = stream.ConsumeIntegral<size_t>();
  field.offset = stream.ConsumeIntegral<size_t>();
  field.descriptor = nullptr;  // Not used in unlabeled_field_pack_to_buffer
  field.default_value = nullptr;  // Not used in unlabeled_field_pack_to_buffer
  field.cname = stream.ConsumeRandomLengthString().c_str();

  // Create a ProtobufCBufferSimple
  ProtobufCBufferSimple buffer_simple = PROTOBUF_C_BUFFER_SIMPLE_INIT(nullptr);

  // Create a ProtobufCBuffer, pointing to our buffer_simple
  ProtobufCBuffer* buffer = (ProtobufCBuffer*)&buffer_simple;

  // Create a member
  std::string member = stream.ConsumeRandomLengthString();
  
  // Call the function to fuzz
  unlabeled_field_pack_to_buffer(&field, (char*)member.c_str(), buffer);

  // Clean up
  PROTOBUF_C_BUFFER_SIMPLE_CLEAR(&buffer_simple);

  return 0;
}