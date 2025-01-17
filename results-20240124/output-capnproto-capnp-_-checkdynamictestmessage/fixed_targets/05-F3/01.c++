#include <capnp/serialize-packed.h>
#include <capnp/serialize.h>
#include <capnp/dynamic.h>

int main() {
  capnp::MallocMessageBuilder message;
  capnp::TestAllTypes::Builder allTypes = message.initRoot<capnp::TestAllTypes>();

  allTypes.setTextField("Hello, world!");
  allTypes.setUInt32Field(12345);

  capnp::DynamicStruct::Builder dynamicStruct = message.initRoot<capnp::DynamicStruct>(2);
  dynamicStruct.set("textField", "Hello, world!");
  dynamicStruct.set("uint32Field", 12345);

  std::string packedMessage = messageToFlatArray(message);

  capnp::PackedMessageReader reader(packedMessage);
  capnp::TestAllTypes::Reader unpackedAllTypes = reader.getRoot<capnp::TestAllTypes>();

  std::string textField = unpackedAllTypes.getTextField();
  uint32_t uint32Field = unpackedAllTypes.getUInt32Field();

  capnp::DynamicStruct::Reader unpackedDynamicStruct = reader.getRoot<capnp::DynamicStruct>();

  std::string textField2 = unpackedDynamicStruct.get("textField").as<std::string>();
  uint32_t uint32Field2 = unpackedDynamicStruct.get("uint32Field").as<uint32_t>();

  return 0;
}