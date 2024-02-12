#include "test-util.h"
#include <kj/main.h>
#include "serialize.h"
#include <capnp/test.capnp.h>
#include <unistd.h>

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
    capnp::DynamicStruct::Builder builder;
    capnp::_::checkDynamicTestMessage(builder.initAs<capnp::_::TestAllTypes>(reader.getRoot<capnp::_::TestAllTypes>()));
    builder.adopt(builder.asReader().getStructFieldByName("int32List"), builder.asReader().getStructFieldByName("int32List").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructFieldByName("int64List"), builder.asReader().getStructFieldByName("int64List").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructFieldByName("float32List"), builder.asReader().getStructFieldByName("float32List").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructFieldByName("float64List"), builder.asReader().getStructFieldByName("float64List").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructFieldByName("boolList"), builder.asReader().getStructFieldByName("boolList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructFieldByName("stringList"), builder.asReader().getStructFieldByName("stringList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructFieldByName("byteList"), builder.asReader().getStructFieldByName("byteList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructFieldByName("enumList"), builder.asReader().getStructFieldByName("enumList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructFieldByName("structList"), builder.asReader().getStructFieldByName("structList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructFieldByName("interfaceList"), builder.asReader().getStructFieldByName("interfaceList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructFieldByName("anyPointerList"), builder.asReader().getStructFieldByName("anyPointerList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructFieldByName("textList"), builder.asReader().getStructFieldByName("textList").getContainingStruct().asOrphan());
    kj::str(builder.asReader());
  })) {
    KJ_LOG(ERROR, "threw");
  }
  return 0;
}