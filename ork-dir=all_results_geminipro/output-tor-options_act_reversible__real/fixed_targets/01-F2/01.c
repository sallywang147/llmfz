#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "orconfig.h"

extern "C" {
#include "options.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string options = stream.ConsumeRemainingBytesAsString();
  struct or_options_t* old_options = or_options_new();
  char* msg = nullptr;
  int ret = options_act_reversible__real(old_options, &msg);
  if (msg) {
    free(msg);
  }
  or_options_free(old_options);
  return ret;
}

#ifdef __cplusplus
extern "C" {
#endif

int or_options_act_reversible__real(struct or_options_t* old_options, char** msg);

#ifdef __cplusplus
}
#endif