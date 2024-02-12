#include <capnp/serialize.h>
#include <capnp/serialize-packed.h>

int main() {
  capnp::MallocMessageBuilder message;
  capnp::DynamicStruct::Builder root = message.initRoot<capnp::DynamicStruct>();
  return 0;
}