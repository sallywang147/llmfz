#include <capnp/message.h>
#include <capnp/serialize-packed.h>

namespace capnp {
namespace _ {
  void checkDynamicTestMessage(DynamicStruct const&);
}  // namespace _
}  // namespace capnp

int main() {
  capnp::PackedMessageReader message;
  capnp::DynamicStructReader struct_reader = message.getRoot<capnp::DynamicStruct>();
  capnp::_::checkDynamicTestMessage(struct_reader);
  return 0;
}