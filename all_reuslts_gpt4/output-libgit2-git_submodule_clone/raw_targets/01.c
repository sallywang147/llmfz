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

  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  git_repository *repo = NULL;
  git_submodule *submodule = NULL;
  git_submodule_update_options opts;
  git_submodule_update_options_init(&opts, GIT_SUBMODULE_UPDATE_OPTIONS_VERSION);

  // Initialize a new repository in a new directory
  char repodir[] = "/tmp/fuzz_repo_XXXXXX";
  if (!mkdtemp(repodir)) {
    return 0;
  }

  if (git_repository_init(&repo, repodir, 0) != 0) {
    return 0;
  }

  // Create a new submodule
  std::string url = provider.ConsumeRandomLengthString();
  std::string path = provider.ConsumeRandomLengthString();
  if (git_submodule_add_setup(&submodule, repo, url.c_str(), path.c_str(), 1) != 0) {
    git_repository_free(repo);
    return 0;
  }

  // Clone the submodule
  git_submodule_clone(&repo, submodule, &opts);

  git_repository_free(repo);
  git_submodule_free(submodule);

  return 0;
}