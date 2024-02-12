#include <capnp/dynamic.h>
#include <capnp/serialize.h>
#include <capnp/test.capnp.h>

int main() {
  capnp::DynamicStruct msg = capnp::DynamicStruct::Builder::initRoot<capnp::DynamicTestMessage>();
  capnp::checkDynamicTestMessage(msg);
  return 0;
}