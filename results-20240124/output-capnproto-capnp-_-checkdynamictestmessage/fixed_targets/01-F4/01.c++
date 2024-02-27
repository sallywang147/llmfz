#include <capnp/dynamic.h>

extern "C" {
#include <capnp/test.capnp.h>
}

int main() {
  capnp::DynamicStruct msg = capnp::DynamicStruct::Builder::initRoot<capnp::DynamicTestMessage>();
  capnp::checkDynamicTestMessage(msg);
  return 0;
}