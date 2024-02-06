#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "git2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    git_libgit2_init();
    initialized = true;
  }

  git_repository* repo = nullptr;
  git_submodule* submodule = nullptr;
  git_submodule_update_options opts;

  FuzzedDataProvider provider(data, size);

  // Initialize git_submodule_update_options with default values
  git_submodule_update_options_init(&opts, GIT_SUBMODULE_UPDATE_OPTIONS_VERSION);

  // Consume data from the fuzzer input
  opts.clone_checkout_strategy = provider.ConsumeIntegral<unsigned int>();
  opts.fetch_recurse_submodules = provider.ConsumeIntegral<int>();
  opts.ignore = provider.ConsumeIntegral<int>();
  opts.checkout_opts.checkout_strategy = provider.ConsumeIntegral<unsigned int>();
  opts.checkout_opts.disable_filters = provider.ConsumeBool();
  opts.checkout_opts.file_mode = provider.ConsumeIntegral<unsigned int>();
  opts.checkout_opts.dir_mode = provider.ConsumeIntegral<unsigned int>();

  // Call the function to be fuzzed
  git_submodule_clone(&repo, submodule, &opts);

  // Cleanup
  if (repo) {
    git_repository_free(repo);
  }

  return 0;
}