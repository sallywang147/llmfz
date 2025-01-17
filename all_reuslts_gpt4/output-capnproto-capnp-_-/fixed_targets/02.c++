#include <fuzzer/FuzzedDataProvider.h>
#include <capnp/dynamic.h>
#include <capnp/message.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize a Cap'n Proto message and its root as a DynamicStruct.
  capnp::MallocMessageBuilder message;
  capnp::DynamicStruct::Builder builder = message.initRoot<capnp::DynamicStruct>();

  // Consume the fuzzing data and use it to populate the DynamicStruct.
  while (stream.remaining_bytes() > 0) {
    // Consume a string from the fuzzing data.
    std::string key = stream.ConsumeRandomLengthString();

    // Consume a boolean from the fuzzing data.
    bool value = stream.ConsumeBool();

    // Set the field in the DynamicStruct.
    builder.set(key, value);
  }

  // Call the target function.
  capnp::_::(builder);

  return 0;
}