#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "orconfig.h"
#include "or.h"
#include "config.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize Tor
  tor_init(0, NULL);

  // Create a new options object
  or_options_t *options = options_new();
  
  if (options == NULL) {
    return 0;
  }

  // Fill the options object with fuzzed data
  options->SocksPort_set = stream.ConsumeIntegral<int>();
  options->ControlPort_set = stream.ConsumeIntegral<int>();
  options->AvoidDiskWrites = stream.ConsumeBool();
  options->ClientOnly = stream.ConsumeBool();

  // Call the function to fuzz
  int result = options_act__real(options);

  // Cleanup
  or_options_free(options);

  return 0;
}