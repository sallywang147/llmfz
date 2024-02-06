#include <fuzzer/FuzzedDataProvider.h>
#include <git2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  
  git_libgit2_init();

  struct git_repository *repo = NULL;
  struct git_clone_options clone_options = GIT_CLONE_OPTIONS_INIT;

  std::string url = fuzzed_data.ConsumeBytesAsString(fuzzed_data.ConsumeIntegralInRange<size_t>(0, size));
  std::string local_path = fuzzed_data.ConsumeRemainingBytesAsString();

  int error = git_clone__submodule(&repo, (char *)url.c_str(), (char *)local_path.c_str(), &clone_options);

  if(repo != NULL) {
    git_repository_free(repo);
  }

  git_libgit2_shutdown();

  return 0;
}