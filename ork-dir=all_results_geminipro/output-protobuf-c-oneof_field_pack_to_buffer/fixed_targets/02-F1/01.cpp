#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "protobuf-c.h"

extern "C" {
#include "oneof_field.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t field_descriptor_size = stream.ConsumeIntegral<size_t>();
  const size_t oneof_case = stream.ConsumeIntegral<int>();
  const size_t member_size = stream.ConsumeIntegral<size_t>();
  const size_t buffer_size = stream.ConsumeIntegral<size_t>();

  struct ProtobufCFieldDescriptor field_descriptor;
  char* member = static_cast<char*>(malloc(member_size));
  stream.ConsumeBytes(member, member_size);
  struct ProtobufCBuffer buffer;
  char* buffer_data = static_cast<char*>(malloc(buffer_size));
  protobuf_c_buffer_init(&buffer, buffer_data, buffer_size);

  oneof_field_pack_to_buffer(&field_descriptor, oneof_case, member, &buffer);

  protobuf_c_buffer_destroy(&buffer);
  free(member);
  free(buffer_data);
  return 0;
}