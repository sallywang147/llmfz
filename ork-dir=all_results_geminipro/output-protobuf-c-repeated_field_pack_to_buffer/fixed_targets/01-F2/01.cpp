#include <assert.h>
#include <fuzzing/memory.hpp>
#include <stdlib.h>

#include "protobuf-c.h"

extern "C" {
#include "repeated_field.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ProtobufCBuffer buffer;
  protobuf_c_buffer_init(&buffer, 0, NULL);

  ProtobufCFieldDescriptor field;
  field.name = "field";
  field.label = PROTOBUF_C_LABEL_REPEATED;
  field.type = PROTOBUF_C_TYPE_INT32;
  field.offset = 0;

  for (int i = 0; i < 100; i++) {
    int count = rand() % 100;
    char *member = (char *)malloc(count * sizeof(int));
    for (int j = 0; j < count; j++) {
      ((int *)member)[j] = rand();
    }

    size_t len = repeated_field_pack_to_buffer(&field, count, member, &buffer);
    uint8_t *copy = (uint8_t *)malloc(len);
    protobuf_c_buffer_copy(copy, &buffer);

    fuzzing::memory::memory_test(copy, len);

    protobuf_c_buffer_free(&buffer);
    free(copy);
    free(member);
  }

  return 0;
}