#include <fuzzer/FuzzedDataProvider.h>
#include <protobuf-c/protobuf-c.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// Assuming we have a message type `MyMessage` defined in our protobuf schema.
extern "C" ProtobufCMessage* my_message_new(void);
extern "C" void my_message_free(ProtobufCMessage* msg);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new message
  ProtobufCMessage* message = my_message_new();
  if (message == nullptr) {
    return 0;
  }

  // Unpack the message from the data
  size_t unpacked_size = protobuf_c_message_unpack(my_message_get_descriptor(),
                                                   nullptr, size, data, message);
  if (unpacked_size == 0) {
    my_message_free(message);
    return 0;
  }

  // Create a buffer
  std::vector<uint8_t> buffer(size);
  ProtobufCBufferSimple bs = PROTOBUF_C_BUFFER_SIMPLE_INIT(buffer.data());

  // Pack the message to the buffer
  protobuf_c_message_pack_to_buffer(message, &(bs.base));

  // Clean up
  my_message_free(message);
  PROTOBUF_C_BUFFER_SIMPLE_CLEAR(&bs);

  return 0;
}