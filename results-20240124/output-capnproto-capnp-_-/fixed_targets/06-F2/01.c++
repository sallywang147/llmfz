#include "test-util.h"
#include <kj/main.h>
#include "serialize.h"
#include <capnp/test.capnp.h>
#include <unistd.h>

extern "C" {
#include <libFuzzer/libFuzzer.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {
  kj::ArrayPtr<const uint8_t> array(Data, Size);
  kj::ArrayInputStream ais(array);

  KJ_IF_MAYBE(e, kj::runCatchingExceptions([&]() {
    capnp::InputStreamMessageReader reader(ais);
    capnp::DynamicStruct::Builder builder;
    capnp::_::checkDynamicTestMessage(reader.getRoot<capnp::DynamicStruct>(builder.asReader()));
    kj::str(reader.getRoot<capnp::_::TestAllTypes>());
  })) {
    KJ_LOG(ERROR, "threw");
  }
  return 0;
}