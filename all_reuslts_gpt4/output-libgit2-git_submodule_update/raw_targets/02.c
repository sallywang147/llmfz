#include <fuzzer/FuzzedDataProvider.h>
#include <git2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    git_libgit2_init();
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize the git_submodule struct
  git_submodule *sm = nullptr;

  // Initialize the git_submodule_update_options struct
  git_submodule_update_options update_options;
  git_submodule_update_options_init(&update_options, GIT_SUBMODULE_UPDATE_OPTIONS_VERSION);

  // Consume data from the fuzzer input
  int init = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed
  git_submodule_update(sm, init, &update_options);

  return 0;
}