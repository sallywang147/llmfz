#include <hermes/hermes.h>
#include <jsi/jsi.h>
#include <fuzzer/FuzzedDataProvider.h>

using facebook::hermes::HermesRuntime;
using facebook::hermes::makeHermesRuntime;
using facebook::jsi::HostObject;
using facebook::jsi::JSIException;
using facebook::jsi::Object;
using facebook::jsi::PropNameID;
using facebook::jsi::Runtime;
using facebook::jsi::String;
using facebook::jsi::StringBuffer;
using facebook::jsi::Value;
using hermes::vm::NativeArgs;
using hermes::vm::createDynamicFunction;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (!size) {
    // Hermes can't handle empty input, and it would have a performance cost
    // to do so.
    return 0;
  }
  // Hermes bytecode is assumed to be trusted, and there are often no checks
  // for validity (for performance purposes).
  // Discard inputs that would be interpreted as bytecode to avoid reporting
  // those as errors.
  if (HermesRuntime::isHermesBytecode(data, size)) {
    return 0;
  }

  std::string s(reinterpret_cast<const char *>(data), size);
  s.append("\0");
  auto runtime = makeHermesRuntime();

  FuzzedDataProvider stream(data, size);

  // Consume the data to create the arguments for the function
  int int_arg = stream.ConsumeIntegral<int>();

  // Create a NativeArgs object
  NativeArgs args;

  // Call the function with the arguments
  createDynamicFunction(runtime.get(), &args, int_arg);

  return 0;
}