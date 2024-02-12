#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hermes/hermes.h"
#include "hermes/vm/Callable.h"
#include "hermes/vm/Runtime.h"
#include "hermes/vm/StringPrimitive.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (!size) {
    // Hermes can't handle empty input, and it would have a performance cost
    // to do so.
    return 0;
  }
  // Hermes bytecode is assumed to be trusted, and there are often no checks
  // for validity (for performance purposes).
  // Discard inputs that would be interpreted as bytecode to avoid reporting
  // those as errors.
  if (hermes::vm::HermesRuntime::isHermesBytecode(data, size)) {
    return 0;
  }

  std::string s(reinterpret_cast<const char *>(data), size);
  s.append("\0");
  auto runtime = hermes::makeHermesRuntime();

  // create a simple HostObject
  class ProtoHostObject : public hermes::vm::HostObject {
    hermes::vm::Value get(hermes::vm::Runtime &rt, const hermes::vm::PropNameID &)
        override {
      return hermes::vm::StringPrimitive::createAscii(rt, "phoprop");
    }

    void set(hermes::vm::Runtime &, const hermes::vm::PropNameID &name,
             const hermes::vm::Value &value) override {
      (void)name;
      (void)value;
      return;
    }

    std::vector<hermes::vm::PropNameID> getPropertyNames(
        hermes::vm::Runtime &rt) override {
      return hermes::vm::PropNameID::names(rt, "prop1", "1", "2", "prop2", "3");
    }
  };

  // expose the HostObject to the js runtime
  // many important apps expose this kind of objects
  runtime->global().setProperty(
      *runtime,
      "p",
      hermes::vm::Object::createFromHostObject(
          *runtime, std::make_shared<ProtoHostObject>()));

  // Cap the run-time of the code so that fuzzing can stay efficient.
  constexpr uint32_t kTimeoutForRunningInMs = 10000;
  runtime->watchTimeLimit(kTimeoutForRunningInMs);

  try {
    runtime->evaluateJavaScript(std::make_unique<hermes::StringBuffer>(s), "");
  } catch (const hermes::vm::JSIException &e) {
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

extern "C" {
void hermes::vm::functionConstructor(char *ptr,
                                               hermes::vm::Runtime *runtime,
                                               hermes::vm::NativeArgs *args) {
  // This function is not implemented, and the fuzzer harness will not call it.
  (void)ptr;
  (void)runtime;
  (void)args;
}
}