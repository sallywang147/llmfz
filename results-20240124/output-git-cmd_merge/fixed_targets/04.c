#include <algorithm>  // for std::sort
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

extern "C" {
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
#include "cmd_merge.h"
#include "cmd_mv.h"
#include "cmd_rerere.h"
#include "cmd_status.h"
#include "fuzzer/FuzzedDataProvider.h"
#include "help.h"
#include "load_builtin_commands.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int argc = stream.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    std::string arg = stream.ConsumeRemainingBytesAsString();
    argv.push_back(strdup(arg.c_str()));
  }
  std::string cmd = stream.ConsumeRemainingBytesAsString();
  std::sort(argv.begin(), argv.end());  // sort the arguments
  if (cmd == "add") {
    cmd_add(argc, argv.data());
  } else if (cmd == "branch") {
    cmd_branch(argc, argv.data());
  } else if (cmd == "commit") {
    cmd_commit(argc, argv.data());
  } else if (cmd == "config") {
    cmd_config(argc, argv.data());
  } else if (cmd == "diff") {
    cmd_diff(argc, argv.data());
  } else if (cmd == "diff-files") {
    cmd_diff_files(argc, argv.data());
  } else if (cmd == "diff-index") {
    cmd_diff_index(argc, argv.data());
  } else if (cmd == "diff-tree") {
    cmd_diff_tree(argc, argv.data());
  } else if (cmd == "init-db") {
    cmd_init_db(argc, argv.data());
  } else if (cmd == "ls-files") {
    cmd_ls_files(argc, argv.data());
  } else if (cmd == "ls-tree") {
    cmd_ls_tree(argc, argv.data());
  } else if (cmd == "merge") {
    cmd_merge(argc, argv.data());
  } else if (cmd == "mv") {
    cmd_mv(argc, argv.data());
  } else if (cmd == "rerere") {
    cmd_rerere(argc, argv.data());
  } else if (cmd == "status") {
    cmd_status(argc, argv.data());
  }
  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }
  return 0;
}