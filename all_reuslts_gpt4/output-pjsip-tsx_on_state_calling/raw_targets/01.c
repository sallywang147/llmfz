#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pjsip.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct pjsip_transaction tsx;
  struct pjsip_event event;

  // Initialize transaction and event with fuzzed data
  provider.ConsumeData(&tsx, sizeof(tsx));
  provider.ConsumeData(&event, sizeof(event));

  // Call the function under test
  int result = tsx_on_state_calling(&tsx, &event);

  return 0;
}