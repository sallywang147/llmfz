#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "git2/errors.h"
#include "git2/rebase.h"

extern "C" {
#include "git2/cmd/add.h"
#include "git2/cmd/branch.h"
#include "git2/cmd/commit.h"
#include "git2/cmd/config.h"
#include "git2/cmd/diff.h"
#include "git2/cmd/diff_files.h"
#include "git2/cmd/diff_index.h"
#include "git2/cmd/diff_tree.h"
#include "git2/cmd/init_db.h"
#include "git2/cmd/ls_files.h"
#include "git2/cmd/ls_tree.h"
#include "git2/cmd/mv.h"
#include "git2/cmd/rerere.h"
#include "git2/cmd/status.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct rebase_options rebase_opts = {0};
  rebase_opts.quiet = provider.ConsumeBool();
  rebase_opts.verbose = provider.ConsumeBool();
  rebase_opts.signoff = provider.ConsumeBool();
  rebase_opts.allow_conflicts = provider.ConsumeBool();
  rebase_opts.allow_empty_commits = provider.ConsumeBool();
  rebase_opts.autostash = provider.ConsumeBool();
  rebase_opts.ignore_whitespace = provider.ConsumeBool();
  rebase_opts.ignore_uncommitted = provider.ConsumeBool();
  rebase_opts.ignore_untracked = provider.ConsumeBool();
  rebase_opts.merge = provider.ConsumeBool();
  rebase_opts.no_ff = provider.ConsumeBool();
  rebase_opts.no_rewritten_commit = provider.ConsumeBool();
  rebase_opts.preserve_merges = provider.ConsumeBool();
  rebase_opts.quiet_conflicts = provider.ConsumeBool();
  rebase_opts.signoff = provider.ConsumeBool();
  rebase_opts.skip = provider.ConsumeBool();
  rebase_opts.strategy = provider.ConsumeIntegral<git_rebase_strategy>();
  rebase_opts.upstream = provider.ConsumeBool();
  rebase_opts.verbose = provider.ConsumeBool();

  int result = run_sequencer_rebase(&rebase_opts);
  if (result != 0 && result != GIT_EUSER) {
    abort();
  }

  return 0;
}