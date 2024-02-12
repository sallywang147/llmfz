#include <capnp/message.h>
#include <capnp/dynamic.h>

int main() {
  capnp::DynamicStructReader dynamic_message = capnp::DynamicStruct::Builder::initRoot<capnp::DynamicStruct>(0).asReader();
  capnp::_::checkDynamicTestMessage(dynamic_message);
  return 0;
}