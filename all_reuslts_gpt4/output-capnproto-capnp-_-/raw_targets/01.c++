#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <capnp/dynamic.h>
#include <capnp/message.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  capnp::MallocMessageBuilder message;
  capnp::DynamicStruct::Builder builder = message.initRoot<capnp::DynamicStruct>();

  if (stream.remaining_bytes() > 0) {
    auto remaining = stream.ConsumeRemainingBytes<uint8_t>();
    builder.set("data", kj::ArrayPtr<const uint8_t>(remaining.data(), remaining.size()));
  }

  capnp::_::(builder);

  return 0;
}