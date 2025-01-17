#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "orconfig.h"
#include "options.h"

extern "C" {
#include "or.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t num_options = stream.ConsumeIntegral<size_t>();
  struct or_options_t *old_options =
      static_cast<struct or_options_t *>(calloc(1, sizeof(struct or_options_t)));
  if (old_options == nullptr) {
    return 0;
  }
  for (size_t i = 0; i < num_options; i++) {
    const char *option_name = stream.ConsumeRemainingBytesAsString().c_str();
    const char *option_value = stream.ConsumeRemainingBytesAsString().c_str();
    or_options_set_string(old_options, option_name, option_value);
  }
  const int result = options_act__real(old_options);
  or_options_free(old_options);
  return result;
}