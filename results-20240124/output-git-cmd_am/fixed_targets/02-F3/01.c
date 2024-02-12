#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "cmd_am.h"
#include "cmd_add.h"
#include "cmd_branch.h"
#include "cmd_commit.h"
#include "cmd_config.h"
#include "cmd_diff.h"
#include "cmd_diff_files.h"
#include "cmd_diff_index.h"
#include "cmd_diff_tree.h"
#include "cmd_init_db.h"
#include "cmd_ls_files.h"
#include "cmd_ls_tree.h"
#include "cmd_mv.h"
#include "cmd_rerere.h"
#include "cmd_status.h"
#include "load_builtin_commands.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int argc = stream.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    const std::string arg = stream.ConsumeRemainingBytesAsString();
    argv.push_back(const_cast<char*>(arg.c_str()));
  }
  const std::string env = stream.ConsumeRemainingBytesAsString();
  char* envp[] = {const_cast<char*>(env.c_str()), nullptr};

  // Fix: Call the intended function instead of the undeclared 'cmd_am'.
  cmd_am(argc, argv.data(), envp[0]);

  return 0;
}