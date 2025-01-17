#include <capnp/message.h>
#include <capnp/serialize.h>

extern "C" {
#include <capnp/generated/test.capnp.h>
}

void capnp::_::checkDynamicTestMessage(capnp::DynamicStruct::Builder * builder) {
  // Do nothing.
}

int main() {
  capnp::MallocMessageBuilder message;
  test::TestMessage::Builder testMessage = message.initRoot<test::TestMessage>();
  testMessage.setFoo("Hello, world!");
  capnp::writeMessageToFd(1, message);
  return 0;
}