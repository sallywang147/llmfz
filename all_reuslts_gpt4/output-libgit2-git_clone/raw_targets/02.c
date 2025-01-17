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

  FuzzedDataProvider provider(data, size);

  git_repository *repo = nullptr;
  git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;

  // Consume data from the provider to initialize the parameters for git_clone
  std::string url = provider.ConsumeRandomLengthString();
  std::string local_path = provider.ConsumeRandomLengthString();

  // Call the function to fuzz
  git_clone(&repo, url.c_str(), local_path.c_str(), &clone_opts);

  if (repo) {
    git_repository_free(repo);
  }

  return 0;
}