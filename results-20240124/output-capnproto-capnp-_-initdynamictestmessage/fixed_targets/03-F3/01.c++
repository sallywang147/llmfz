#include "test-util.h"
#include <kj/main.h>
#include "serialize.h"

#include <capnp/test.capnp.h>
#include <unistd.h>

extern "C" {
#include "serialize.h"
}

/* This is the entry point of a fuzz target to be used with libFuzzer
 * or another fuzz driver.
 * Such a fuzz driver is used by the autotools target capnp-llvm-fuzzer-testcase
 * when the environment variable LIB_FUZZING_ENGINE is defined
 * for instance LIB_FUZZING_ENGINE=-fsanitize=fuzzer for libFuzzer
 */

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {
  kj::ArrayPtr<const uint8_t> array(Data, Size);
  kj::ArrayInputStream ais(array);

  KJ_IF_MAYBE(e, kj::runCatchingExceptions([&]() {
    capnp::InputStreamMessageReader reader(ais);
    capnp::_::TestAllTypes::Builder builder;
    capnp::_::initDynamicTestMessage(builder.initDynamicStruct());
    capnp::_::checkDynamicTestMessage(builder.asDynamicStruct(capnp::Schema::from<capnp::_::TestAllTypes>()));
    kj::str(builder.asDynamicStruct());
  })) {
    KJ_LOG(ERROR, e->getDescription());
  }
  return 0;
}