#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "git2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    git_libgit2_init();
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);
  
  // Initialize a git_submodule struct
  git_submodule *sm = nullptr;

  // Initialize a git_submodule_update_options struct
  git_submodule_update_options update_options;
  git_submodule_update_options_init(&update_options, GIT_SUBMODULE_UPDATE_OPTIONS_VERSION);

  // Consume data from the stream
  int init = stream.ConsumeIntegral<int>();

  // Call the target function
  int ret = git_submodule_update(sm, init, &update_options);

  return 0;
}