 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "sequencer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct rebase_options options;

  options.verbose = stream.ConsumeBool();
  options.quiet = stream.ConsumeBool();
  options.force = stream.ConsumeBool();
  options.verbose_log = stream.ConsumeBool();
  options.dry_run = stream.ConsumeBool();
  options.allow_conflicts = stream.ConsumeBool();
  options.allow_missing_commits = stream.ConsumeBool();
  options.signoff = stream.ConsumeBool();
  options.auto_commit = stream.ConsumeBool();
  options.commit_msg = stream.ConsumeRemainingBytesAsString();
  options.commit_msg_file = stream.ConsumeRemainingBytesAsString();

  run_sequencer_rebase(&options);
  return 0;
}