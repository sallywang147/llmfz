#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "capnp/dynamic.h"
#include "capnp/message.h"
#include "capnp/schema.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a message and a root builder.
  capnp::MallocMessageBuilder message;
  auto root = message.initRoot<capnp::DynamicStruct>();

  // Create a schema for the builder.
  capnp::StructSchema schema;
  capnp::StructSchema::Field field;

  // Create an orphan.
  capnp::MallocMessageBuilder orphanMessage;
  auto orphan = capnp::Orphanage::getForMessageContaining(orphanMessage).newOrphan<capnp::DynamicStruct>();

  // Adopt the orphan into the root builder.
  root.adopt(field, kj::mv(orphan));

  return 0;
}