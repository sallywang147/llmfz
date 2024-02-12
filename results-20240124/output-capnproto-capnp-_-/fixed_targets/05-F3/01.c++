#include <capnp/message.h>
#include <capnp/serialize.h>
#include <capnp/serialize-packed.h>

extern "C" {
#include <capnp/dynamic.h>
#include <capnp/dynamic-serialize.h>
}

int main() {
  capnp::DynamicStruct::Builder message = capnp::DynamicStruct::Builder::initRoot(capnp::defaultGlobal());
  capnp::_::checkDynamicTestMessage(message);
  return 0;
}