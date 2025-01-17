#include "serialize.h"
#include "test-util.h"
#include <capnp/test.capnp.h>
#include <kj/main.h>
#include <unistd.h>

extern "C" {
#include <capnp/dynamic.h>
}

/* This is the entry point of a fuzz target to be used with libFuzzer
 * or another fuzz driver.
 * Such a fuzz driver is used by the autotools target capnp-llvm-fuzzer-testcase
 * when the environment variable LIB_FUZZING_ENGINE is defined
 * for instance LIB_FUZZING_ENGINE=-fsanitize=fuzzer for libFuzzer
 */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  kj::ArrayPtr<const uint8_t> array(Data, Size);
  kj::ArrayInputStream ais(array);

  if (kj::none != kj::runCatchingExceptions([&]() {
        capnp::InputStreamMessageReader reader(ais);
        capnp::_::checkTestMessage(reader.getRoot<capnp::_::TestAllTypes>());
        capnp::_::checkDynamicTestMessage(reader.getRoot<capnp::DynamicStruct>(capnp::Schema::from<capnp::_::TestAllTypes>()));
        capnp::DynamicStruct::Builder builder = reader.getRoot<capnp::DynamicStruct>(capnp::Schema::from<capnp::_::TestAllTypes>()).asBuilder();
        builder.adopt(builder.which(), builder.get(builder.which()).asOrphan());
        kj::str(builder.asReader());
      })) {
    KJ_LOG(ERROR, "threw");
  }
  return 0;
}