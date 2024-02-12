#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include "cmd_merge.h"
#include "cmd_status.h"
#include "cmd_add.h"
#include "cmd_commit.h"
#include "cmd_init_db.h"
#include "cmd_branch.h"
#include "cmd_diff.h"
#include "cmd_diff_files.h"
#include "cmd_diff_tree.h"
#include "cmd_diff_index.h"
#include "load_builtin_commands.h"
#include "cmd_ls_files.h"
#include "cmd_config.h"
#include "cmd_rerere.h"
#include "cmd_ls_tree.h"
#include "cmd_mv.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t argc = provider.ConsumeIntegralInRange<size_t>(0, 10);
  std::vector<char*> argv(argc + 1);
  for (size_t i = 0; i < argc; i++) {
    const size_t arg_size = provider.ConsumeIntegralInRange<size_t>(0, 100);
    std::string arg = provider.ConsumeBytesAsString(arg_size);
    argv[i] = strdup(arg.c_str());
  }
  argv[argc] = nullptr;

  const size_t config_size = provider.ConsumeIntegralInRange<size_t>(0, 100);
  std::string config = provider.ConsumeBytesAsString(config_size);
  cmd_merge(argc, argv.data(), config.c_str());

  for (size_t i = 0; i < argc; i++) {
    free(argv[i]);
  }
  return 0;
}