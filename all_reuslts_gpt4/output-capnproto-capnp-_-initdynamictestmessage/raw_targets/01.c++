#include <fuzzer/FuzzedDataProvider.h>
#include <capnp/dynamic.h>
#include <capnp/message.h>
#include <capnp/serialize.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  capnp::MallocMessageBuilder message;
  auto builder = message.initRoot<capnp::DynamicStruct>();

  capnp::_::initDynamicTestMessage(&builder);

  return 0;
}