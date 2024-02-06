#include <fuzzer/FuzzedDataProvider.h>
#include <capnp/dynamic.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <kj/io.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a message and a builder for the message
  capnp::MallocMessageBuilder message;
  capnp::DynamicStruct::Builder builder = message.initRoot<capnp::DynamicStruct>();

  // Consume the data to fill the builder
  while (stream.remaining_bytes() > 0) {
    // Consume a string
    std::string str = stream.ConsumeRandomLengthString();
    // Add the string to the builder
    builder.set(str.c_str(), capnp::Data::Reader(reinterpret_cast<const kj::byte*>(str.data()), str.size()));
  }

  // Call the function to fuzz
  capnp::_::checkDynamicTestMessage(&builder);

  return 0;
}