#include <fuzzer/FuzzedDataProvider.h>

#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "hermes/VM/Runtime.h"
#include "hermes/VM/StringPrimitive.h"
#include "hermes/VM/Value.h"

using namespace hermes::vm;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  Runtime runtime(RuntimeConfig::Builder().build());
  // Create a NativeArgs object.
  NativeArgs args;
  // Create a HermesValue object.
  HermesValue value;
  // Create a vector of HermesValue objects.
  std::vector<HermesValue> values;
  // Create a vector of StringPrimitive objects.
  std::vector<StringPrimitive*> strings;
  // Create a vector of const char* objects.
  std::vector<const char*> cstrings;

  // Generate a random number of arguments.
  size_t numArgs = provider.ConsumeIntegralInRange<size_t>(0, 10);
  // Generate a random number of values.
  size_t numValues = provider.ConsumeIntegralInRange<size_t>(0, 10);
  // Generate a random number of strings.
  size_t numStrings = provider.ConsumeIntegralInRange<size_t>(0, 10);
  // Generate a random number of cstrings.
  size_t numCStrings = provider.ConsumeIntegralInRange<size_t>(0, 10);

  // Generate the arguments.
  for (size_t i = 0; i < numArgs; i++) {
    args.arguments.emplace_back(provider.ConsumeIntegral<int32_t>());
  }

  // Generate the values.
  for (size_t i = 0; i < numValues; i++) {
    values.emplace_back(provider.ConsumeIntegral<int32_t>());
  }

  // Generate the strings.
  for (size_t i = 0; i < numStrings; i++) {
    size_t strSize = provider.ConsumeIntegralInRange<size_t>(0, 100);
    std::string str = provider.ConsumeRandomLengthString(strSize);
    strings.emplace_back(StringPrimitive::create(runtime, str));
  }

  // Generate the cstrings.
  for (size_t i = 0; i < numCStrings; i++) {
    size_t strSize = provider.ConsumeIntegralInRange<size_t>(0, 100);
    std::string str = provider.ConsumeRandomLengthString(strSize);
    cstrings.emplace_back(str.c_str());
  }

  // Call the function.
  createDynamicFunction(&runtime, &args, 0);

  // Clean up.
  for (auto& str : strings) {
    str->release();
  }

  return 0;
}