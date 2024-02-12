#include <capnp/message.h>
#include <capnp/serialize-packed.h>

int main() {
  capnp::MallocMessageBuilder message;
  capnp::_::initDynamicTestMessage(message.getRoot<capnp::DynamicStruct::Builder>());
  return 0;
}