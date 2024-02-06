#include <fuzzer/FuzzedDataProvider.h>
#include <protobuf-c/protobuf-c.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for oneof_field_pack_to_buffer
  ProtobufCFieldDescriptor field;
  int oneof_case = stream.ConsumeIntegral<int>();
  std::string member_str = stream.ConsumeRandomLengthString();
  char *member = const_cast<char*>(member_str.c_str());

  // Define and initialize a ProtobufCBuffer
  ProtobufCBufferSimple buffer = PROTOBUF_C_BUFFER_SIMPLE_INIT(nullptr);

  // Define and initialize a ProtobufCFieldDescriptor
  field.name = "fuzzed_field";
  field.id = stream.ConsumeIntegral<uint32_t>();
  field.label = static_cast<ProtobufCLabel>(stream.ConsumeIntegralInRange<int>(PROTOBUF_C_LABEL_REQUIRED, PROTOBUF_C_LABEL_REPEATED));
  field.type = static_cast<ProtobufCType>(stream.ConsumeIntegralInRange<int>(PROTOBUF_C_TYPE_INT32, PROTOBUF_C_TYPE_MESSAGE));
  field.quantifier_offset = stream.ConsumeIntegral<uint32_t>();
  field.offset = stream.ConsumeIntegral<uint32_t>();
  field.descriptor = nullptr;
  field.flags = stream.ConsumeIntegral<uint32_t>();
  field.default_value = nullptr;

  // Call the function to fuzz
  oneof_field_pack_to_buffer(&field, oneof_case, member, &buffer.base);

  // Free the buffer
  PROTOBUF_C_BUFFER_SIMPLE_CLEAR(&buffer);

  return 0;
}