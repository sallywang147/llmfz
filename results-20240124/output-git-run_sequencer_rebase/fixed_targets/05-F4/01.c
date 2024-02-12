#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "git2/errors.h"
#include "git2/rebase.h"
#include "git2/repository.h"

extern "C" {
#include "git2/cmd.h"
#include "git2/errors.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  git_repository* repo = nullptr;
  if (git_repository_open(&repo, ".") != GIT_OK) {
    return 0;
  }

  git_rebase_options rebase_opts = GIT_REBASE_OPTIONS_INIT;
  rebase_opts.quiet = true;
  rebase_opts.verbose = true;
  rebase_opts.signoff = true;
  rebase_opts.autostash = true;

  int ret = run_sequencer_rebase(&rebase_opts);
  if (ret != GIT_OK) {
    git_error_clear();
  }

  git_repository_free(repo);

  return 0;
}