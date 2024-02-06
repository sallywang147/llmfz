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

  FuzzedDataProvider stream(data, size);

  // Consume data for the url and local_path
  std::string url = stream.ConsumeRandomLengthString();
  std::string local_path = stream.ConsumeRemainingBytesAsString();

  // Initialize the git_clone_options structure
  git_clone_options options = GIT_CLONE_OPTIONS_INIT;

  // Initialize the git_repository pointer
  git_repository *repo = nullptr;

  // Call the target function
  git_clone(&repo, url.c_str(), local_path.c_str(), &options);

  // Cleanup
  if (repo) {
    git_repository_free(repo);
  }

  return 0;
}