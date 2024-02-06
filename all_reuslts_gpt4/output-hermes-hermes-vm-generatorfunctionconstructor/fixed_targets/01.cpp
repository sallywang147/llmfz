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

  class ProtoHostObject : public HostObject {
    Value get(Runtime &rt, const PropNameID &) override { return String::createFromAscii(rt, "phoprop"); }

    void set(Runtime &, const PropNameID &name, const Value &value) override {
      (void)name;
      (void)value;
      return;
    }

    std::vector<PropNameID> getPropertyNames(Runtime &rt) override { return PropNameID::names(rt, "prop1", "1", "2", "prop2", "3"); }
  };

  runtime->global().setProperty(*runtime, "p", Object::createFromHostObject(*runtime, std::make_shared<ProtoHostObject>()));

  constexpr uint32_t kTimeoutForRunningInMs = 10000;
  runtime->watchTimeLimit(kTimeoutForRunningInMs);

  // FuzzedDataProvider is a class to consume fuzzing input.
  FuzzedDataProvider stream(data, size);

  // Consume data using FuzzedDataProvider.
  std::string str = stream.ConsumeRandomLengthString();
  char *char_ptr = const_cast<char*>(str.c_str());

  hermes::vm::NativeArgs args;

  try {
    hermes::vm::generatorFunctionConstructor(char_ptr, runtime.get(), &args);
  } catch (const JSIException &e) {
    // Swallow JS-based exceptions.
  }

  return 0;
}