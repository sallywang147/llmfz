#include <fuzzing/memory.hpp>
#include <protobuf-c/protobuf-c.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ProtobufCBuffer buffer;
  protobuf_c_buffer_init(&buffer, 0, NULL);
  protobuf_c_buffer_append(&buffer, data, size);

  ProtobufCMessageDescriptor *descriptor = protobuf_c_descriptor_get_by_name("Foo__TestMessageCheck");
  ProtobufCMessage message;
  protobuf_c_message_init(&message, descriptor);

  size_t len = oneof_field_pack_to_buffer(descriptor->fields[0], 1, &message, &buffer);
  uint8_t *copy = (uint8_t *)malloc(len);
  oneof_field_pack_to_buffer(descriptor->fields[0], 1, &message, &buffer);
  fuzzing::memory::memory_test(copy, len);
  free(copy);

  protobuf_c_message_free(&message);
  protobuf_c_buffer_fini(&buffer);

  return 0;
}