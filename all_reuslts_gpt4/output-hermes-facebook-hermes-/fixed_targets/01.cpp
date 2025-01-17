#include <hermes/hermes.h>
#include <jsi/jsi.h>
#include <hermes/VM/RuntimeConfig.h>

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
using facebook::jsi::detail::ThreadSafeRuntimeImpl;
using hermes::vm::RuntimeConfig;

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

  // create a simple HostObject
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

  try {
    runtime->evaluateJavaScript(std::make_unique<StringBuffer>(s), "");
  } catch (const JSIException &e) {
  }

  // Initialize the RuntimeConfig
  RuntimeConfig config;

  // Call the ThreadSafeRuntimeImpl function
  ThreadSafeRuntimeImpl<facebook::hermes::HermesRuntimeImpl, facebook::hermes::makeHermesRuntime>(runtime.get(), &config);

  return 0;
}