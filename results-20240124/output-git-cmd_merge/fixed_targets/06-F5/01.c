#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "cmd_merge.h"
#include "cmd_branch.h"
#include "cmd_diff.h"
#include "cmd_diff_files.h"
#include "cmd_diff_tree.h"
#include "cmd_diff_index.h"
#include "cmd_add.h"
#include "cmd_commit.h"
#include "cmd_init_db.h"
#include "load_builtin_commands.h"
#include "cmd_status.h"
#include "cmd_ls_files.h"
#include "cmd_config.h"
#include "cmd_rerere.h"
#include "cmd_ls_tree.h"
#include "cmd_mv.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int argc = stream.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    argv.push_back(const_cast<char*>(stream.ConsumeRemainingBytesAsString().c_str()));
  }
  char* envp = nullptr;
  cmd_merge(argc, argv.data(), envp);
  return 0;
}