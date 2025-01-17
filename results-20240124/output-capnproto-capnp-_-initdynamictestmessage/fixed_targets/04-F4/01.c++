#include <capnp/dynamic.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  capnp::MallocMessageBuilder message;
  capnp::DynamicStruct::Builder builder = message.initRoot<capnp::DynamicStruct>();
  capnp::_::initDynamicTestMessage(&builder);

  FuzzedDataProvider fuzzed_data_provider(data, size);
  fuzzed_data_provider.ConsumeBytes<capnp::word>(builder.size());
  capnp::writePackedMessageToFd(message, 1);
  return 0;
}