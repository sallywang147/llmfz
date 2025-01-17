#include <capnp/message.h>
#include <capnp/serialize.h>

int main() {
  capnp::MallocMessageBuilder message;
  capnp::DynamicStruct::Builder root = message.initRoot<capnp::DynamicStruct>();

  // Add a field to the struct.
  root.set("name", "Alice");

  // Serialize the message to a byte array.
  std::string bytes = message.toFlattenedString();

  // Deserialize the message from the byte array.
  capnp::FlatArrayMessageReader reader(bytes);
  capnp::DynamicStruct::Reader deserializedRoot = reader.getRoot<capnp::DynamicStruct>();

  // Print the value of the field.
  std::cout << deserializedRoot.get("name").asString() << std::endl;

  return 0;
}