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
    capnp::_::checkDynamicTestMessage(builder.init<capnp::_::TestAllTypes>(reader.getRoot<capnp::_::TestAllTypes>()));
    builder.adopt(builder.asReader().getStructField("int32List"), builder.asReader().getStructField("int32List").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructField("int64List"), builder.asReader().getStructField("int64List").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructField("float32List"), builder.asReader().getStructField("float32List").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructField("float64List"), builder.asReader().getStructField("float64List").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructField("boolList"), builder.asReader().getStructField("boolList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructField("stringList"), builder.asReader().getStructField("stringList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructField("byteList"), builder.asReader().getStructField("byteList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructField("enumList"), builder.asReader().getStructField("enumList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructField("structList"), builder.asReader().getStructField("structList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructField("interfaceList"), builder.asReader().getStructField("interfaceList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructField("anyPointerList"), builder.asReader().getStructField("anyPointerList").getContainingStruct().asOrphan());
    builder.adopt(builder.asReader().getStructField("textList"), builder.asReader().getStructField("textList").getContainingStruct().asOrphan());
    kj::str(builder.asReader());
  })) {
    KJ_LOG(ERROR, "threw");
  }
  return 0;
}