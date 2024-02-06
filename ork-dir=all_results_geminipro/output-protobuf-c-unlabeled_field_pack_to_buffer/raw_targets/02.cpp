#include <fuzzing/memory.hpp>
#include <protobuf-c/protobuf-c.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ProtobufCBuffer buffer;
  protobuf_c_buffer_init(&buffer, 0, NULL);

  FuzzedDataProvider stream(data, size);
  const size_t field_count = stream.ConsumeIntegralInRange<size_t>(0, 10);
  ProtobufCFieldDescriptor *fields[field_count];
  char *members[field_count];
  for (size_t i = 0; i < field_count; ++i) {
    fields[i] = (ProtobufCFieldDescriptor *)stream.ConsumeIntegral<uint64_t>();
    members[i] = (char *)stream.ConsumeIntegral<uint64_t>();
  }

  for (size_t i = 0; i < field_count; ++i) {
    size_t len = unlabeled_field_pack_to_buffer(fields[i], members[i], &buffer);
    uint8_t *copy = (uint8_t *)malloc(len);
    protobuf_c_buffer_copy(copy, &buffer);
    fuzzing::memory::memory_test(copy, len);
    free(copy);
  }

  protobuf_c_buffer_fini(&buffer);
  return 0;
}