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
    capnp::DynamicStruct::Builder builder = capnp::DynamicStruct::builder();
    capnp::_::checkDynamicTestMessage(builder.initAs<capnp::_::TestAllTypes>(reader.getRoot<capnp::_::TestAllTypes>()));
    builder.adopt(builder.getProto().getStructSchema().getFieldByName("int32List"), builder.getProto().getStructSchema().getFieldByName("int32List").getContainingStruct().asOrphan());
    builder.adopt(builder.getProto().getStructSchema().getFieldByName("int64List"), builder.getProto().getStructSchema().getFieldByName("int64List").getContainingStruct().asOrphan());
    builder.adopt(builder.getProto().getStructSchema().getFieldByName("float32List"), builder.getProto().getStructSchema().getFieldByName("float32List").getContainingStruct().asOrphan());
    builder.adopt(builder.getProto().getStructSchema().getFieldByName("float64List"), builder.getProto().getStructSchema().getFieldByName("float64List").getContainingStruct().asOrphan());
    builder.adopt(builder.getProto().getStructSchema().getFieldByName("boolList"), builder.getProto().getStructSchema().getFieldByName("boolList").getContainingStruct().asOrphan());
    builder.adopt(builder.getProto().getStructSchema().getFieldByName("stringList"), builder.getProto().getStructSchema().getFieldByName("stringList").getContainingStruct().asOrphan());
    builder.adopt(builder.getProto().getStructSchema().getFieldByName("byteList"), builder.getProto().getStructSchema().getFieldByName("byteList").getContainingStruct().asOrphan());
    builder.adopt(builder.getProto().getStructSchema().getFieldByName("enumList"), builder.getProto().getStructSchema().getFieldByName("enumList").getContainingStruct().asOrphan());
    builder.adopt(builder.getProto().getStructSchema().getFieldByName("structList"), builder.getProto().getStructSchema().getFieldByName("structList").getContainingStruct().asOrphan());
    builder.adopt(builder.getProto().getStructSchema().getFieldByName("interfaceList"), builder.getProto().getStructSchema().getFieldByName("interfaceList").getContainingStruct().asOrphan());
    builder.adopt(builder.getProto().getStructSchema().getFieldByName("anyPointerList"), builder.getProto().getStructSchema().getFieldByName("anyPointerList").getContainingStruct().asOrphan());
    builder.adopt(builder.getProto().getStructSchema().getFieldByName("textList"), builder.getProto().getStructSchema().getFieldByName("textList").getContainingStruct().asOrphan());
    kj::str(builder.asReader());
  })) {
    KJ_LOG(ERROR, "threw");
  }
  return 0;
}