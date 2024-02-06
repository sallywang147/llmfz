#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <capnp/dynamic.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <kj/array.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a message builder.
  capnp::MallocMessageBuilder message;

  // Get the root object of the message.
  capnp::DynamicStruct::Builder builder = message.initRoot<capnp::DynamicStruct>();

  // Consume the data from the fuzzing input.
  while (stream.remaining_bytes() > 0) {
    // Consume a field number and a value for the field.
    uint16_t fieldNumber = stream.ConsumeIntegral<uint16_t>();
    int64_t value = stream.ConsumeIntegral<int64_t>();

    // Set the field in the message.
    capnp::DynamicValue::Builder fieldValue = builder.init(fieldNumber, capnp::schema::Type::INT64);
    fieldValue.as<capnp::DynamicInt64>() = value;
  }

  // Pass the message to the function to be fuzzed.
  capnp::_::checkDynamicTestMessage(&builder);

  return 0;
}