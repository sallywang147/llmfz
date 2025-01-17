#include <capnp/message.h>
#include <capnp/dynamic.h>
#include <capnp/test.capnp.h>
#include <kj/main.h>
#include <unistd.h>

/* This is the entry point of a fuzz target to be used with libFuzzer
 * or another fuzz driver.
 * Such a fuzz driver is used by the autotools target capnp-llvm-fuzzer-testcase
 * when the environment variable LIB_FUZZING_ENGINE is defined
 * for instance LIB_FUZZING_ENGINE=-fsanitize=fuzzer for libFuzzer
 */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  capnp::DynamicStruct::Builder builder;
  capnp::_::(builder);
  return 0;
}