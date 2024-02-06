#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "orconfig.h"

extern "C" {
#include "or/or.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  or_options_t *options = or_options_new();
  if (options == nullptr) {
    return 0;
  }

  or_options_set_defaults(options);

  char *msg = nullptr;
  const int result = options_act_reversible__real(options, &msg);
  if (result != 0) {
    or_options_free(options);
    tor_free(msg);  // Use tor_free instead of free
    return 0;
  }

  or_options_free(options);
  tor_free(msg);  // Use tor_free instead of free
  return 0;
}