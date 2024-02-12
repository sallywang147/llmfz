 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

#include "hermes/hermes.h"
#include "hermes/vm/Runtime.h"
#include "hermes/vm/NativeArgs.h"
#include "hermes/vm/StringPrimitive.h"
#include "hermes/vm/Value.h"
#include "hermes/vm/vm-string-inl.h"

using facebook::hermes::HermesRuntime;
using facebook::hermes::makeHermesRuntime;
using facebook::hermes::vm::Runtime;
using facebook::hermes::vm::NativeArgs;
using facebook::hermes::vm::StringPrimitive;
using facebook::hermes::vm::Value;

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

  // Cap the run-time of the code so that fuzzing can stay efficient.
  constexpr uint32_t kTimeoutForRunningInMs = 10000;
  runtime->watchTimeLimit(kTimeoutForRunningInMs);

  try {
    runtime->evaluateJavaScript(std::make_unique<StringPrimitive>(s), "");
  } catch (const Value &e) {
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