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
  std::string url = provider.ConsumeRandomLengthString();
  std::string local_path = provider.ConsumeRandomLengthString();

  git_clone_options options;
  git_clone_options_init(&options, GIT_CLONE_OPTIONS_VERSION);

  int use_existing = provider.ConsumeBool();

  git__clone(&repo, const_cast<char*>(url.c_str()), const_cast<char*>(local_path.c_str()), &options, use_existing);

  if(repo != nullptr) {
    git_repository_free(repo);
  }

  return 0;
}