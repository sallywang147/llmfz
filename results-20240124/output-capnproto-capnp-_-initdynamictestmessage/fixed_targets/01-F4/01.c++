#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "capnp/message.h"
#include "capnp/serialize.h"

extern "C" {
#include "capnp/dynamic.h"
}

void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  capnp::DynamicStruct::Builder builder = capnp::DynamicStruct::Builder::initRoot(
      capnp::defaultAllocator);
  capnp::_::initDynamicTestMessage(&builder);

  FuzzedDataProvider fdp(data, size);
  capnp::writeMessageToFd(builder.asReader(), fdp.ConsumeInt<int>());
}