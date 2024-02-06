#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <capnp/dynamic.h>
#include <capnp/message.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  capnp::MallocMessageBuilder message;
  auto root = message.initRoot<capnp::DynamicStruct>();
  capnp::_::initDynamicTestMessage(&root);
  return 0;
}