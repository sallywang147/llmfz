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
    return 0;
  }

  if (HermesRuntime::isHermesBytecode(data, size)) {
    return 0;
  }

  std::string s(reinterpret_cast<const char *>(data), size);
  s.append("\0");
  auto runtime = makeHermesRuntime();

  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = const_cast<char*>(str.c_str());

  // Create a NativeArgs object
  NativeArgs args;

  try {
    hermes::vm::asyncFunctionConstructor(ptr, runtime.get(), &args);
  } catch (const JSIException &e) {
    // Swallow JS-based exceptions.
  }

  return 0;
}