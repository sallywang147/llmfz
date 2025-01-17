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
  
  git_repository *repo = NULL;
  git_clone_options options = GIT_CLONE_OPTIONS_INIT;

  std::string url = stream.ConsumeRandomLengthString();
  std::string local_path = stream.ConsumeRandomLengthString();

  git_clone__submodule(&repo, const_cast<char*>(url.c_str()), const_cast<char*>(local_path.c_str()), &options);

  git_repository_free(repo);

  return 0;
}