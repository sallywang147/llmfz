#include <fuzzer/FuzzedDataProvider.h>
#include <protobuf-c/protobuf-c.h>

#include <cstdint>
#include <cstddef>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize a ProtobufCMessage
  ProtobufCMessage message;
  message.descriptor = nullptr; // Set to null for simplicity
  message.n_unknown_fields = 0;
  message.unknown_fields = nullptr;

  // Define and initialize a ProtobufCBufferSimple
  ProtobufCBufferSimple buffer_simple = PROTOBUF_C_BUFFER_SIMPLE_INIT(nullptr);
  ProtobufCBuffer *buffer = (ProtobufCBuffer *)&buffer_simple;

  // Call the function to fuzz
  protobuf_c_message_pack_to_buffer(&message, buffer);

  // Cleanup
  PROTOBUF_C_BUFFER_SIMPLE_CLEAR(&buffer_simple);

  return 0;
}