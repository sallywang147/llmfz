 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "capnp/message.h"
#include "capnp/serialize.h"
#include "capnp/test.capnp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  capnp::MallocMessageBuilder message;
  capnp::DynamicStruct::Builder root = message.initRoot<capnp::DynamicStruct>(
      capnp::Schema::from<capnp::_::TestAllTypes>());

  capnp::_::initDynamicTestMessage(&root);
  return 0;
}