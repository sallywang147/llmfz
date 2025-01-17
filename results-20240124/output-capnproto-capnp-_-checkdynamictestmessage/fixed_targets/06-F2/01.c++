#include <capnp/message.h>
#include <capnp/serialize.h>
#include <capnp/serialize-packed.h>
#include <capnp/dynamic.h>
#include <capnp/test.capnp.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "check_test_message.h"
}

void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  capnp::DynamicStruct::Builder builder;
  capnp::_::checkDynamicTestMessage(&builder);
  FuzzedDataProvider fuzzed_data(data, size);
  capnp::writePackedMessage(builder, fuzzed_data.ConsumeBytes(size));
}