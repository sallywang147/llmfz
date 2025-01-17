#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize the action structure.
  struct action a;
  a.type = provider.ConsumeIntegralInRange<int>(0, 10);
  a.next = provider.ConsumeIntegralInRange<int>(0, 10);
  a.u.i = provider.ConsumeIntegralInRange<int>(0, 10);

  // Call the function to be fuzzed.
  int result = fix_actions(&a);

  // Check the return value of the function.
  if (result != 0) {
    // The function returned an error.
    return 0;
  }

  // The function succeeded.
  return 0;
}