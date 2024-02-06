#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "capnp/dynamic.h"
#include "capnp/schema.h"
#include "capnp/message.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a message and a builder for the dynamic struct.
  capnp::MallocMessageBuilder message;
  auto dynamicStructBuilder = message.initRoot<capnp::DynamicStruct>();

  // Create a schema for the field.
  capnp::StructSchema::Field field;

  // Create an orphan based on the remaining data.
  auto orphan = capnp::Orphan<capnp::DynamicValue>::create(capnp::DynamicValue::Reader(capnp::DynamicStruct::Reader()));

  // Try to adopt the orphan using the dynamic struct builder.
  try {
    dynamicStructBuilder.adopt(&field, &orphan);
  } catch (const capnp::Exception& e) {
    // Ignore exceptions for fuzzing.
  }

  return 0;
}