#include <capnp/serialize.h>
#include <capnp/serialize-packed.h>

extern "C" {
#include <capnp/dynamic.h>
}

int main() {
  capnp::MallocMessageBuilder message;
  capnp::DynamicStruct::Builder root = message.initRoot<capnp::DynamicStruct>();
  capnp::_::initDynamicTestMessage(&root);
  return 0;
}