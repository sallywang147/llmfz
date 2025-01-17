#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>
#include <hermes/hermes.h>
#include <jsi/jsi.h>

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

namespace {

class ProtoHostObject : public HostObject {
 public:
  Value get(Runtime &rt, const PropNameID &) override {
    return String::createFromAscii(rt, "phoprop");
  }

  void set(Runtime &, const PropNameID &name, const Value &value) override {
    (void)name;
    (void)value;
    return;
  }

  std::vector<PropNameID> getPropertyNames(Runtime &rt) override {
    return PropNameID::names(rt, "prop1", "1", "2", "prop2", "3");
  }
};

}  // namespace

extern "C" {
void createDynamicFunction(Runtime *runtime, NativeArgs *args, int) {
  args->getThis(*runtime).asObject(*runtime).setProperty(*runtime, "p", Object::createFromHostObject(
                                                                     *runtime, std::make_shared<ProtoHostObject>()));
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
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

  // Cap the run-time of the code so that fuzzing can stay efficient.
  constexpr uint32_t kTimeoutForRunningInMs = 10000;
  runtime->watchTimeLimit(kTimeoutForRunningInMs);

  try {
    runtime->evaluateJavaScript(std::make_unique<StringBuffer>(s), "");
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
}