#include "test-util.h"
#include <kj/main.h>
#include "serialize.h"
#include <unistd.h>

extern "C" {
#include <capnp/test.capnp.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {
  kj::ArrayPtr<const uint8_t> array(Data, Size);
  kj::ArrayInputStream ais(array);

  KJ_IF_MAYBE(e, kj::runCatchingExceptions([&]() {
    capnp::InputStreamMessageReader reader(ais);
    capnp::_::(reader.getRoot<capnp::DynamicStruct>(capnp::Schema::from<capnp::_::TestAllTypes>()).builder());
  })) {
    KJ_LOG(ERROR, "threw");
  }
  return 0;
}

int main(int argc, char** argv) {
  return kj::main(argc, argv);
}