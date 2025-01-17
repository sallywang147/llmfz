#include <capnp/message.h>
#include <capnp/serialize-packed.h>

extern "C" {
#include <capnp/dynamic.h>
}

int main() {
  capnp::MallocMessageBuilder message;
  capnp::DynamicStruct::Builder root = message.initRoot<capnp::DynamicStruct>();

  // Set the "dynamicTestMessage" field to true.
  root.set("dynamicTestMessage", true);

  // Serialize the message to a packed format.
  std::string packedMessage;
  capnp::serializePackedMessageToFlatArray(message, &packedMessage);

  // Deserialize the message from the packed format.
  capnp::FlatArrayMessageReader reader(packedMessage);
  capnp::DynamicStruct::Reader deserializedRoot = reader.getRoot<capnp::DynamicStruct>();

  // Check if the "dynamicTestMessage" field is true.
  bool dynamicTestMessage = deserializedRoot.get("dynamicTestMessage").as<bool>();

  // Print the value of the "dynamicTestMessage" field.
  std::cout << "dynamicTestMessage: " << dynamicTestMessage << std::endl;

  return 0;
}