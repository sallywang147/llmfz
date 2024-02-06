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

  FuzzedDataProvider stream(data, size);
  std::string s = stream.ConsumeRandomLengthString();
  s.append("\0");
  auto runtime = makeHermesRuntime();
  NativeArgs args;

  try {
    hermes::vm::functionConstructor(const_cast<char*>(s.c_str()), runtime.get(), &args);
  } catch (const JSIException &e) {
    // Swallow JS-based exceptions.
    // The fuzzer will generate a lot of invalid JS, and if this causes an
    // exception to be thrown evaluating it, that's alright.
    // The fuzzer is more interested in inputs that cause the sort of crash that
    // doesn't throw an exception.
  }
  // Other types of exceptions are not ok to occur, and should be reported as
  // bugs.
  // Hermes throws no exceptions during normal operation, with the exception of
  // any that escape JS.
  return 0;
}