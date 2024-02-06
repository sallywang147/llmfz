#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "protobuf-c/protobuf-c.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the ProtobufCFieldDescriptor.
  ProtobufCFieldDescriptor field;
  field.label = stream.ConsumeEnum<ProtobufCLabel>();
  field.name = stream.ConsumeRandomLengthString().c_str();
  field.id = stream.ConsumeIntegral<uint32_t>();
  field.offset = stream.ConsumeIntegral<size_t>();
  field.type = stream.ConsumeEnum<ProtobufCType>();
  field.quantifier_offset = stream.ConsumeIntegral<size_t>();
  field.descriptor = nullptr; // Set to null as we don't have a valid descriptor to use.

  // Define and initialize the count.
  int count = stream.ConsumeIntegralInRange<int>(0, 100);

  // Define and initialize the member.
  std::vector<char> memberVec = stream.ConsumeBytes<char>(count);
  char* member = memberVec.data();

  // Define and initialize the ProtobufCBuffer.
  ProtobufCBufferSimple buffer_simple = PROTOBUF_C_BUFFER_SIMPLE_INIT(NULL);
  ProtobufCBuffer* buffer = &buffer_simple.base;

  // Call the function to fuzz.
  repeated_field_pack_to_buffer(&field, count, member, buffer);

  // Cleanup
  PROTOBUF_C_BUFFER_SIMPLE_CLEAR(&buffer_simple);

  return 0;
}