#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include <sysexits.h>
#include <unistd.h>
#include "git2/blob.h"
#include "git2/commit.h"
#include "git2/diff.h"
#include "git2/index.h"
#include "git2/merge.h"
#include "git2/oid.h"
#include "git2/object.h"
#include "git2/reflog.h"
#include "git2/remote.h"
#include "git2/repository.h"
#include "git2/signature.h"
#include "git2/stash.h"
#include "git2/status.h"
#include "git2/submodule.h"
#include "git2/tag.h"
#include "git2/tree.h"
#include "git2/worktree.h"

#include "cmd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string arg1 = stream.ConsumeRandomLengthString();
  const std::string arg2 = stream.ConsumeRandomLengthString();
  const std::string arg3 = stream.ConsumeRandomLengthString();
  std::vector<char*> argv = {const_cast<char*>(arg1.c_str()),
                             const_cast<char*>(arg2.c_str()),
                             const_cast<char*>(arg3.c_str())};
  execv("/usr/bin/cmd_merge", argv.data());
  return 0;
}