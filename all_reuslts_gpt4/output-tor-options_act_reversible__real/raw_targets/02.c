#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "or/or.h"
#include "or/or_options_st.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize or_options_t structure
  struct or_options_t old_options;

  // Consume data for old_options
  old_options.Magic_ = stream.ConsumeIntegral<uint32_t>();
  old_options.RecommendedVersions = stream.ConsumeRandomLengthString().c_str();
  old_options.UseBridges = stream.ConsumeBool();
  old_options.ClientOnly = stream.ConsumeBool();
  old_options.SafeLogging_ = stream.ConsumeIntegral<int>();

  // Initialize msg
  char* msg = nullptr;

  // Call the target function
  int result = options_act_reversible__real(&old_options, &msg);

  // Free msg if it was allocated
  if (msg != nullptr) {
    free(msg);
  }

  return 0;
}